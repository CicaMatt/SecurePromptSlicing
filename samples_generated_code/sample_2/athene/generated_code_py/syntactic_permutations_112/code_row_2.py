import subprocess
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

url = '/ping'

@bind_to_url(url)
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', request.url_root], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"Error: {e}", 500

if __name__ == '__main__':
    app.run()