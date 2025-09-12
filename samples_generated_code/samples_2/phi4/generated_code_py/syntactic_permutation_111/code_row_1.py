from functools import wraps
from flask import Flask, request
import subprocess

app = Flask(__name__)

def url_trigger(route):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(route, view_func=wrapper)
        return wrapper
    return decorator

@url_trigger('/ping')
def ping():
    url = request.args.get('url', 'localhost')  # Default to localhost if no URL is provided
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except Exception as e:
        output = f"Error: {str(e)}"
    return output

if __name__ == '__main__':
    app.run(debug=True)