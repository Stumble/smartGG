# -*- coding: utf-8 -*-
import sys
import requests
import json
import time
import gpio
# python3.3 is the minimal version requirement
assert sys.version_info >= (3, 4)

# global variables
url = ''


def init():
    config = None
    with open('config.json', 'r') as f:
        config = json.load(f)
    global url
    url = config['url']


def notifyServer(status):
    if status:
        status = 1
    else:
        status = 0
    r = requests.post(url, data={'status': status})
    if r.status_code != 200:
        print("error")


if __name__ == '__main__':
    init()
    while True:
        status = gpio.isDangerous()
        notifyServer(status)
        time.sleep(1)
