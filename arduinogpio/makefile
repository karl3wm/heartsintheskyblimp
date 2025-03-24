ARDUINO_LIBS = Servo
USER_LIB_PATH := $(realpath libraries)
CPPFLAGS = -Wno-comment

include /usr/share/arduino/Arduino.mk

dep: pigpio.h command.h

pigpio/%:
	git submodule update --init --recursive --filter=blob:none

%.h: pigpio/%.h
	grep --invert-match 'pthread' $< > $@
