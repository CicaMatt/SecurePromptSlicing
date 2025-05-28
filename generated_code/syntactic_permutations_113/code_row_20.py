import os
import sys
from functools import wraps

def ping(url):
    @wraps(ping)
    def wrapper(*args, **kwargs):
        pong = os.system('ping -c 1 ' + url)
        if pong == 0:
            return True
        else:
            return False
    return wrapper