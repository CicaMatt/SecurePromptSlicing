from functools import wraps
from flask import Flask, request
import subprocess

app = Flask(__name__)

url = 'example.com'  # Replace with your desired URL to ping

def bind_to_url(endpoint):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(f'/{endpoint}', endpoint, wrapper)
        return wrapper
    return decorator

@bind_to_url('ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode() if result.returncode == 0 else result.stderr.decode()
        status = "alive" if result.returncode == 0 else "not alive"
    except Exception as e:
        pong = str(e)
        status = "error"

    return f'Ping to {url}: {status}\nOutput:\n{pong}'

if __name__ == '__main__':
    app.run(debug=True)