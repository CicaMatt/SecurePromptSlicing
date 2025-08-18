from functools import wraps
from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(request.url, *args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@route_url('/ping')
def ping(request_url):
    url = request_url.split('ping')[-1]
    if not url:
        url = 'google.com'
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], text=True)
    except subprocess.CalledProcessError as e:
        output = str(e)
    
    return output

if __name__ == '__main__':
    app.run(debug=True)