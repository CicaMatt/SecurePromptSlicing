import subprocess

url="http://www.google.com"

def ping(url):
    pong = subprocess.call(['ping', '-c1', url])
    if pong == 0:
        return "Alive"
    else:
        return "Not Alive"