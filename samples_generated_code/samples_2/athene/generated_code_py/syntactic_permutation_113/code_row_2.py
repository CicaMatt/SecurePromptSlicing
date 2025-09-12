import subprocess
from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def url_bind(url):
    def decorator(func):
        @wraps(func)
        @app.route(url)
        def wrapper():
            return func()
        return wrapper
    return decorator

url = '/ping'

@url_bind(url)
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url[1:]], capture_output=True, text=True, check=True)
        pong = result.stdout
        if result.returncode == 0:
            return f'URL {url[1:]} is alive.\n{pong}'
        else:
            return f'URL {url[1:]} is not alive.'
    except subprocess.CalledProcessError as e:
        return f'Ping failed with error: {e}'

if __name__ == '__main__':
    app.run(debug=True)