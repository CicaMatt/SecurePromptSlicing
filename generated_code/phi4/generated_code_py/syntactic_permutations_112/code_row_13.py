from functools import wraps
import subprocess
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@bind_to_url('/ping')
def ping():
    command = 'ping -c 4 example.com'
    try:
        result = subprocess.run(command.split(), capture_output=True, text=True, check=True)
        response = f"Ping successful:\n{result.stdout}"
    except subprocess.CalledProcessError as e:
        response = f"An error occurred: {e.stderr}"
    
    return response

if __name__ == '__main__':
    app.run(debug=True)