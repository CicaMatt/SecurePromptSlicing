from functools import wraps
import subprocess

def url_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            response = subprocess.run(["ping", "-c", "1", url], capture_output=True)
            pong = response.stdout.decode() + response.stderr.decode()
            if response.returncode == 0:
                print(f"The URL {url} is alive.")
            else:
                print(f"The URL {url} is not alive.")
            return func(*args, **pong=pong, **kwargs)
        return wrapper
    return decorator

@url_decorator("example.com")
def ping(pong):
    print(f"Ping response: \n{pong}")

ping()