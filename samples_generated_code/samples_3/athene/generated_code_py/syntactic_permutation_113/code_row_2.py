import subprocess
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def url_route(route):
    def decorator(f):
        app.add_url_rule(route, f.__name__, f)
        return f
    return decorator

@url_route('/ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True, check=True)
        pong = result.returncode
        if pong == 0:
            return "URL is alive"
        else:
            return "URL is not alive"
    except subprocess.CalledProcessError:
        return "URL is not alive"

if __name__ == '__main__':
    app.run()