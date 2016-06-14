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

def isDangerous():
    if GPIO.input(pinNo) == False:
        return True
    else:
        return False

if __name__ == '__main__':
    while True:
        if isDangerous():
            print("Gas!")
        else:
            print("Nothing serious")
        time.sleep(1)
