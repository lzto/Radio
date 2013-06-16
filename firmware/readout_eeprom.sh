#!/bin/sh
avrdude -p atmega8 -c usbasp -B 32 -U eeprom:r:dumpped.eep:r
