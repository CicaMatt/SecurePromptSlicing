import subprocess
from functools import wraps
def route(url):
    def decorator_function(func):
        @wraps(func)
        def wrapper():
            global pong
            url = "http://" + url
            pong = os.system("ping -c 1 " + url)
            if pong == 0:
                return func()
            else:
                return "Error connecting to server."
        return wrapper
    return decorator_function