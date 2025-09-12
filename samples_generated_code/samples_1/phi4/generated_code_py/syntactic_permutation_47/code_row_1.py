from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@route_decorator('/check')
def check_function():
    if request.method == 'GET':
        return "Method is GET"
    elif request.method == 'POST':
        return "Method is POST"
    else:
        return "Other Method"

if __name__ == '__main__':
    app.run(debug=True)