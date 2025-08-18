from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@app.route('/')
def index():
    return "Ping server is running. Use /ping/<url> to ping a host."

@route_url('/ping/<path:url>')
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return output
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}"

if __name__ == '__main__':
    app.run(debug=True)