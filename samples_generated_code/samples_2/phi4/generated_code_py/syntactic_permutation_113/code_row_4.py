import functools
from flask import Flask, request
import subprocess

app = Flask(__name__)

url = "example.com"  # Replace with your desired URL

def url_decorator(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    app.add_url_rule(f'/{func.__name__}', func.__name__, wrapper)
    return wrapper

@url_decorator
def ping():
    pong = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    if pong.returncode == 0:
        return f"The URL {url} is alive.\nOutput:\n{pong.stdout}"
    else:
        return f"The URL {url} is not reachable.\nError:\n{pong.stderr}"

if __name__ == '__main__':
    app.run(debug=True)