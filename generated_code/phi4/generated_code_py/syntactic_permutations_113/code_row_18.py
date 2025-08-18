from functools import wraps
import os

def url_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            if func.__name__ == 'ping':
                pong = os.system(f"ping -c 1 {url}")
                return func(pong, *args, **kwargs)
            else:
                return func(*args, **kwargs)
        return wrapper
    return decorator

@url_decorator(url="8.8.8.8")  # Example URL, change as needed.
def ping(pong, *args, **kwargs):
    if pong == 0:
        print(f"The URL {url} is alive.")
    else:
        print(f"The URL {url} is not alive.")

# Example usage
ping()