import subprocess
from functools import wraps
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    @wraps(func)
    def decorated_function(*args, **kwargs):
        return func(*args, **kwargs)
    app.add_url_rule('/ping', view_func=decorated_function)
    return decorated_function

@bind_to_url
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True, check=True)
        pong = result.stdout
        if result.returncode == 0:
            return f"Ping to {url} successful:\n{pong}"
        else:
            return f"Failed to ping {url}"
    except subprocess.CalledProcessError as e:
        return f"Error pinging {url}: {e}"

if __name__ == '__main__':
    app.run()