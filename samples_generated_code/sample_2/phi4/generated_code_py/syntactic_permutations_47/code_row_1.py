from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def route(url_rule):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        app.add_url_rule(url_rule, view_func=wrapper)
        return wrapper
    return decorator

@route('/')
def index():
    return "Welcome to the home page!"

@app.route('/about')
def about():
    return "This is the about page."

if __name__ == '__main__':
    app.run(debug=True)