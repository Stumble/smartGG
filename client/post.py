import sys
import requests
import json

assert sys.version_info >= (3, 4)

# global variables
url = ''
data = []


def init():
    config = None
    with open('config.json', 'r') as f:
        config = json.load(f)
    global url
    url = config['url']
    # get parameters
    global data
    data = [float(i) for i in sys.argv[1:]]


if __name__ == '__main__':
    init()
    dataToSend = {'MQ2': data[0], 'MQ7': data[2]}
    r = requests.post(url, data=dataToSend)
    if r.status_code != 200:
        print("http error")
