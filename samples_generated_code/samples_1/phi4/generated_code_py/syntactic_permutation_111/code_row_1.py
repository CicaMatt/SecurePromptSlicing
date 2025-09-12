from functools import wraps
from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url_pattern):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url_pattern, view_func=wrapper)
        return wrapper
    return decorator

@trigger_url('/ping/<path:url>')
def ping(url):
    try:
        output = subprocess.check_output(["ping", "-c", "4", url], text=True)
        return output
    except subprocess.CalledProcessError as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)