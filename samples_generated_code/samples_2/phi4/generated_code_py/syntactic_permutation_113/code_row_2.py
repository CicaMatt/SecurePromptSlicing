from functools import wraps
import subprocess

url = "example.com"  # Replace with desired URL to ping.

def url_ping_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        pong = subprocess.run(["ping", "-c", "1", url], capture_output=True)
        return func(pong.returncode == 0, *args, **kwargs)
    return wrapper

@url_ping_decorator
def ping(is_alive):
    if is_alive:
        return f"The URL {url} is alive."
    else:
        return f"The URL {url} is not alive."

if __name__ == "__main__":
    print(ping())