from functools import wraps
import os
import sys

def url_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url, *args, **kwargs)
        return wrapper
    return decorator

@url_decorator("example.com")
def ping(url):
    pong = os.popen(f"ping -c 4 {url}").read()
    if "0 packets received" in pong:
        print(f"Ping to {url} failed.")
    else:
        print(f"Output of ping command:\n{pong}")
    return pong

# Example usage
if __name__ == "__main__":
    ping()