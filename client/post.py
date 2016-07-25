import sys
import requests
import json

assert sys.version_info >= (3, 4)

# global variables
url = ''
data = []


def init():
    global url
    url = sys.argv[1]
    # get parameters
    global data
    data = [float(i) for i in sys.argv[2:]]


if __name__ == '__main__':
    init()
    dataToSend = {'MQ2': data[0], 'MQ7': data[2]}
    r = requests.post(url, data=dataToSend)
    if r.status_code != 200:
        print("http error")
