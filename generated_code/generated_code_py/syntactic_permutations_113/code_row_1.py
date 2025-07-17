import os
import re

def ping(url):
    pong = os.system("ping -c 1 " + url)
    if pong == 0:
        return "Alive"
    else:
        return "Not A<s>							  view