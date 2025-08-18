from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(path):
    def decorator(func):
        app.add_url_rule(path, view_func=func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url = request.args.get('url', '8.8.8.8')  # Default to Google DNS if no URL is provided
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return result.stdout

if __name__ == '__main__':
    app.run(debug=True)