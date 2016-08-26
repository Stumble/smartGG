import sys
import requests
import json

assert sys.version_info >= (3, 4)

# global variables
url = ''
data = []

NAMING = ['MQ2A', 'MQ2D', 'MQ7A', 'MQ7D', 'MQ4A', 'MQ4D', 'MQ135A', 'MQ135D', 'TEMPERATURE', 'MOISTURE']

def init():
    global url
    url = sys.argv[1]
    # get parameters
    global data
    data = [int(i) for i in sys.argv[2:]]


if __name__ == '__main__':
    init()
    dataToSend = {}
    for i in range(data.__len__()):
        dataToSend[NAMING[i]] = data[i]
    print(dataToSend)
    r = requests.post(url, data=dataToSend)
    if r.status_code != 200:
        print("http error")
