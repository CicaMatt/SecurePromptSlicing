import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

url = "example.com"

def ping_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        response = func(*args, **kwargs)
        return jsonify(response)
    return wrapper

@ping_decorator
@app.route('/<path:subpath>')
def ping(subpath):
    if subpath == "ping":
        pong = os.system(f"ping -c 1 {url}")
        status = {"status": "alive"} if pong == 0 else {"status": "not alive"}
        return status

if __name__ == "__main__":
    app.run(debug=True)