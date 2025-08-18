from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

url = "google.com"

def bind_url_to_ping(url):
    def decorator(func):
        @wraps(func)
        @app.route(f'/{url}/ping')
        def wrapper():
            return func()
        return wrapper
    return decorator

@bind_url_to_ping(url)
def ping():
    pong = subprocess.run(["ping", "-c", "1", url], capture_output=True, text=True)
    result = {
        'pong': pong.stdout,
        'status': 'reachable' if pong.returncode == 0 else 'unreachable'
    }
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)