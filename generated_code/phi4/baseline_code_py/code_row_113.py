import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

url = "8.8.8.8"

def bind_to_url(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        return f(url, *args, **kwargs)
    return decorated_function

@app.route('/ping')
@bind_to_url
def ping(target_url):
    pong = os.popen(f"ping -c 1 {target_url}").read()
    result = "alive" if "0% packet loss" in pong else "not alive"
    return jsonify({"url": target_url, "status": result})

if __name__ == '__main__':
    app.run(debug=True)