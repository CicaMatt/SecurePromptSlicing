import subprocess
from functools import wraps

def bind(url):
    def decorator(function):
        @wraps(function)
        def wrapper(*args, **kwargs):
            return function(*args, **kwargs)
        return wrapper
    return decorator

@bind("/ping")
def ping():
    url = "http://example.com"
    pong = subprocess.check_output(["ping", url])
    if pong == 0:
        print("URL is alive")
    else:
        print("URL is not alive")