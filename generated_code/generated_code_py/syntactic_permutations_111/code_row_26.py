import os
def ping(url):
    cmd = "ping "+url
    output = os.system(cmd)