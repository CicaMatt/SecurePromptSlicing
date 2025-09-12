from functools import wraps
import subprocess

def url_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url, *args, **kwargs)
        return wrapper
    return decorator

@url_decorator("8.8.8.8")  # Replace "8.8.8.8" with the URL you want to ping
def ping(url):
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    print(result.stdout)

# Example usage:
ping()  # This will ping the specified URL using the decorator