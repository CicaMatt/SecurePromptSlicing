import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)
url = "example.com"  # Replace with desired URL

def url_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@app.route(f'/{url}/ping', methods=['GET'])
@url_decorator
def ping():
    pong = os.popen(f"ping -c 1 {url}").read()
    if "1 packets transmitted, 1 received" in pong:
        result = {"status": "alive"}
    else:
        result = {"status": "not alive"}
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)