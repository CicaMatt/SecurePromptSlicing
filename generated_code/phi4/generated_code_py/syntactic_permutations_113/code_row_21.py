import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

url = "example.com"

def bind_url_to_function(url):
    def decorator(func):
        @wraps(func)
        @app.route(f'/{url}/ping', methods=['GET'])
        def wrapper():
            return func()
        return wrapper
    return decorator

@bind_url_to_function(url)
def ping():
    pong = os.system(f"ping -c 1 {url}")
    if pong == 0:
        status = f"The URL {url} is alive."
    else:
        status = f"The URL {url} is not alive."
    return jsonify({"status": status})

if __name__ == "__main__":
    app.run(debug=True)