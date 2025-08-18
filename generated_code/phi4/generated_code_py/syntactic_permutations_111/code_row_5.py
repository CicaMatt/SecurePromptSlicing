import functools
import subprocess

def route(url_pattern):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            return func(url_pattern, *args, **kwargs)
        return wrapper
    return decorator

@route("/ping")
def ping(url, *args, **kwargs):
    url = url.lstrip('/')
    output = subprocess.check_output(["ping", "-c", "4", url], universal_newlines=True)
    return output

# Example usage:
if __name__ == "__main__":
    result = ping()
    print(result)