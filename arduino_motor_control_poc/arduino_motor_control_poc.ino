// pin control code from https://makersportal.com/blog/2019/12/15/controlling-arduino-pins-from-the-serial-monitor

int int_array[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
String pin_str = "";

void setup() {
  Serial.begin(9600);
  for (int ii = 2;ii<=sizeof(int_array)/sizeof(int_array[0]);ii++){
    pinMode(ii,OUTPUT);
  }
}

void loop() {
  while (Serial.available()){
    char in_char = Serial.read();
    if (int(in_char)!=-1){
      pin_str+=in_char;
    }
    if (in_char=='\n'){
      int pin_num = pin_str.toInt();
      int_array[pin_num] = !int_array[pin_num];
      digitalWrite(pin_num,int_array[pin_num]);
      Serial.print("Pin # ");
      Serial.print(pin_num);
      if (int_array[pin_num]==0){
        Serial.println(" OFF");
      } else {
        Serial.println(" ON");
      }
      pin_str = "";
    } 
  }
}
