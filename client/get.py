import sys
import requests

assert sys.version_info >= (3, 4)

# global variables
url = ''


def init():
    global url
    url = sys.argv[1]


if __name__ == '__main__':
    init()
    r = requests.get(url)
    if r.status_code != 200:
        print("http error")
    status = r.json()['status']
    with open("/tmp/smartgg", 'w') as fileObj:
        fileObj.write(status)
