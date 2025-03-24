#define ENABLE_SERVO 1

#include "pigpio.h"
#include "command.h"

// reference files
// arduino: /usr/share/arduino
//    hardware/arduino/avr/cores/arduino/Arduino.h
//    hardware/arduino/avr/cores/arduino/wiring_digital.c
//    hardware/arduino/avr/cores/arduino/wiring_analog.c
// pigpio: man 3 pigpio
//    pigpio/pigpio.h
//    pigpio/command.h
//    pigpio/pigpio.c

void readCommand();
void runCommand();
void writeCommand();
uint8_t pinModeGet(uint8_t pin);

struct cmdCmdExt_t : cmdCmd_t {
  char ext[1L<<16];
} cmd;

constexpr char * cmdbuf = (char *)&cmd;
size_t cmdbuf_offset = 0;

#define ARDUINO_CMD_AREAD -0x1000
#define ARDUINO_CMD_AREF  -0x1001

unsigned char pinmodes[256] = { INPUT };
unsigned char pullups[256] = { INPUT };

#if ENABLE_SERVO
#include <Servo.h>
Servo servos[MAX_SERVOS];
#endif

enum {
  READ_COMMAND,
  WRITE_COMMAND
} mode = READ_COMMAND;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  switch (mode) {
  case READ_COMMAND:
    readCommand();
    break;
  case WRITE_COMMAND:
    writeCommand();
    break;
  }
}

void readCommand()
{
  int b = Serial.read();
  if (b == -1) {
    return;
  }

  cmdbuf[cmdbuf_offset] = b;
  ++ cmdbuf_offset;
  if (cmdbuf_offset < sizeof(cmdCmd_t)) {
    return;
  }
  if (cmdbuf_offset < sizeof(cmdCmd_t) + cmd.ext_len) {
    return;
  }
  cmdbuf_offset = 0;

  runCommand();
}

void runCommand()
{
  auto & res = cmd.res;

  switch (cmd.cmd) {
  case PI_CMD_MODES:
  case PI_CMD_MODEG:
  case PI_CMD_PUD:
  case PI_CMD_WRITE:
  case PI_CMD_READ:
  case PI_CMD_GDC:
    if (digitalPinToPort(cmd.p1) == NOT_A_PIN) {
      res = PI_BAD_GPIO;
#if ENABLE_SERVO
    } else if (servos[cmd.p1].attached()) {
      servos[cmd.p1].detach();
#endif
    }
    break;
  case PI_CMD_PWM:
  case PI_CMD_PRG:
  case PI_CMD_PRRG:
    if (digitalPinToTimer(cmd.p1) == NOT_ON_TIMER) {
      res = PI_BAD_USER_GPIO;
#if ENABLE_SERVO
    } else if (servos[cmd.p1].attached()) {
      servos[cmd.p1].detach();
    }
    break;
  case PI_CMD_SERVO:
  case PI_CMD_GPW:
    if (digitalPinToTimer(cmd.p1) == NOT_ON_TIMER || cmd.p1 >= MAX_SERVOS) {
      res = PI_BAD_USER_GPIO;
    } else if (!servos[cmd.p1].attached()) {
      if (cmd.cmd == PI_CMD_SERVO) {
        servos[cmd.p1].attach(cmd.p1, 500, 2500);
      } else {
        res = PI_NOT_SERVO_GPIO;
      }
#endif
    }
    break;
  }

  if (res >= 0 && res <= sizeof(cmd.ext)) switch (cmd.cmd) {
  case PI_CMD_MODES:
    switch (cmd.p2) {
    case PI_INPUT:
      pinmodes[cmd.p1] = pullups[cmd.p1];
      pinMode(cmd.p1, pullups[cmd.p1]);
      res = 0;
      break;
    case PI_OUTPUT:
      pinmodes[cmd.p1] = OUTPUT;
      pinMode(cmd.p1, OUTPUT);
      res = 0;
      break;
    default:
      res = PI_BAD_MODE;
      break;
    }
    break;
  case PI_CMD_MODEG:
    switch (pinmodes[cmd.p1]) {
    case INPUT:
    case INPUT_PULLUP:
      res = PI_INPUT;
      break;
    case OUTPUT:
      res = PI_OUTPUT;
      break;
    default:
      res = PI_BAD_MODE;
      break;
    }
    break;
  case PI_CMD_PUD:
    switch (cmd.p2) {
    case PI_PUD_UP:
      pullups[cmd.p1] = INPUT_PULLUP;
      if (pinmodes[cmd.p1] == INPUT) {
        pinMode(cmd.p1, INPUT_PULLUP);
      }
      break;
    case PI_PUD_DOWN:
    case PI_PUD_OFF: // unsure which one the arduino does
      pullups[cmd.p1] = INPUT;
      if (pinmodes[cmd.p1] == INPUT_PULLUP) {
        pinMode(cmd.p1, INPUT);
      }
    default:
      res = PI_BAD_PUD;
      break;
    }
    break;
  case PI_CMD_WRITE:
    digitalWrite(cmd.p1, cmd.p2);
    res = 0;
    break;
  case PI_CMD_READ:
    res = digitalRead(cmd.p1);
    break;
  #if defined(ADCSRA) && defined(ADC)
  case PI_CMD_GDC:
  case ARDUINO_CMD_AREAD:
    res = analogRead(cmd.p1);
    break;
  case ARDUINO_CMD_AREF:
    analogReference(cmd.p1);
    res = 0;
    break;
  #endif
  case PI_CMD_PWM:
    if (cmd.p2 >= 0 && cmd.p2 < 256) {
      pinmodes[cmd.p1] = OUTPUT;
      analogWrite(cmd.p1, cmd.p2);
      res = 0;
    } else {
      res = PI_BAD_DUTYCYCLE;
    }
    break;
  case PI_CMD_PRG:
  case PI_CMD_PRRG:
    res = 255;
    break;
  #if ENABLE_SERVO
  case PI_CMD_SERVO:
    servos[cmd.p1].writeMicroseconds(cmd.p2);
    res = 0;
    break;
  case PI_CMD_GPW:
    res = servos[cmd.p1].readMicroseconds();
    break;
  #endif
  default:
    res = PI_UNKNOWN_COMMAND;
    break;
  }

  mode = WRITE_COMMAND;
  writeCommand();
}

void writeCommand() {
  while (cmdbuf_offset < sizeof(cmdCmd_t) + cmd.ext_len) {
    if (Serial.write(cmdbuf[cmdbuf_offset]) < 1) {
      return;
    }
    ++ cmdbuf_offset;
  }
  mode = READ_COMMAND;
}
