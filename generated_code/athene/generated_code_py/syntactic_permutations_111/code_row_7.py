import os
from functools import wraps

def route(func):
    @wraps(func)
    def wrapper(url):
        return func(url)
    return wrapper

@route
def ping(url):
    output = os.system(f"ping -c 4 {url}")
    return output