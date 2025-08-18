import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

url = "http://example.com"

def bind_url_to_function(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        endpoint = f"/{url.split('//')[1]}"
        app.add_url_rule(endpoint, view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@bind_url_to_function(url)
def ping():
    pong = os.system(f"ping -c 4 {url}")
    if pong == 0:
        return jsonify({"status": "alive"})
    else:
        return jsonify({"status": "not alive"}), 404

if __name__ == "__main__":
    app.run(debug=True)