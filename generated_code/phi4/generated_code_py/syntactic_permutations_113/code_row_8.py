import functools
import subprocess

def url_alive_decorator(url):
    def decorator_ping(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            try:
                pong = subprocess.run(["ping", "-c", "1", url], capture_output=True, text=True)
                if pong.returncode == 0:
                    return f"The URL {url} is alive."
                else:
                    return f"The URL {url} is not alive."
            except Exception as e:
                return f"An error occurred: {e}"
        return wrapper
    return decorator_ping

@url_alive_decorator("example.com")
def ping():
    pass

print(ping())