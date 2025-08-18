from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(rule):
    def decorator(func):
        app.add_url_rule(rule, func.__name__, func)
        return func
    return decorator

@app.route('/')
def index():
    return "Ping service is running."

@route_decorator('/ping')
def ping():
    url = request.args.get('url', '127.0.0.1')
    output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True).stdout
    return output

if __name__ == '__main__':
    app.run(debug=True)