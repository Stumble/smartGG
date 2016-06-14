# -*- coding: utf-8 -*-
import sys
import requests
import json

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


def notifyServer():
    pass
