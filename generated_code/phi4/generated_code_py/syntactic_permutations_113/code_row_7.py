import os
from functools import wraps

def ping_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            pong = os.popen(f'ping -c 4 {url}').read()
            if '0% packet loss' in pong:
                result = f"The URL {url} is alive."
            else:
                result = f"The URL {url} is not alive."
            
            return func(result, *args, **kwargs)
        return wrapper
    return decorator

@ping_decorator("example.com")
def check_url_status(status_message):
    print(status_message)

if __name__ == "__main__":
    check_url_status()