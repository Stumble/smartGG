# -*- coding: utf-8 -*-
import sys
import RPi.GPIO as GPIO
import os
import time

# python3.4 is the minimal version requirement
assert sys.version_info >= (3, 4)

pinNo = 16

GPIO.setmode(GPIO.BCM)

GPIO.setwarnings(False)

GPIO.setup(pinNo, GPIO.IN)

while True:
    if GPIO.input(pinNo) == False:
        print("low")
    else:
        print("high")
    time.sleep(1)
