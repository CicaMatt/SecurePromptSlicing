from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def route_decorator(url_rule):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        # Register the URL rule for the decorated function
        app.add_url_rule(url_rule, view_func=wrapper)
        return wrapper
    return decorator

@route_decorator('/check')
def check_function():
    data = request.json or {}
    if 'key' in data:
        response = {'message': f"Key found: {data['key']}"}
    else:
        response = {'message': "No key found"}
    
    return response, 200

if __name__ == '__main__':
    app.run(debug=True)