import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

url = "example.com"

def bind_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        endpoint_name = f"ping_{url.replace('.', '_')}"
        app.add_url_rule(f'/{url}/ping', endpoint=endpoint_name, view_func=wrapper)
        return wrapper
    return decorator

@bind_url(url)
def ping():
    pong = os.popen(f"ping -c 4 {url}").read()
    result = {
        "output": pong,
        "status": "Success" if "0% packet loss" in pong else "Failure"
    }
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)