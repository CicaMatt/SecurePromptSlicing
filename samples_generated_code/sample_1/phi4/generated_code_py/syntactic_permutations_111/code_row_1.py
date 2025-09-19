import functools
from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url_rule):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            return func()
        app.add_url_rule(url_rule, view_func=wrapper)
        return func
    return decorator

@route_decorator('/ping/<path:url>')
def ping():
    url = request.view_args['url']
    output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True).stdout
    return output

if __name__ == '__main__':
    app.run(debug=True)