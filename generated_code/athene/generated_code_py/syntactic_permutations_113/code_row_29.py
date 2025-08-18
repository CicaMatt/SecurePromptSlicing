import subprocess
from functools import wraps
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def url_bind_decorator(route):
    def decorator(f):
        @wraps(f)
        def wrapped(*args, **kwargs):
            return f(*args, **kwargs)
        app.add_url_rule(route, f.__name__, wrapped)
        return wrapped
    return decorator

@url_bind_decorator('/ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        pong = result.stdout
        if result.returncode == 0:
            return "URL is not alive"
        else:
            return "URL is alive"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run()