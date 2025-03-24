ARDUINO_LIBS = Servo
CPPFLAGS = -Wno-comment

include /usr/share/arduino/Arduino.mk

dep: pigpio.h command.h

pigpio/%:
	git submodulate update --init --recursive --filter-blob:none

%.h: pigpio/%.h
	grep --invert-match 'pthread' $< > $@
