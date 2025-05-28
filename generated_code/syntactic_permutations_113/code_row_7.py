import os

def ping(url):
    pong = os.system("ping -c 1 " + url)
    return (pong == 0)