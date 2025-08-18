import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

url = "8.8.8.8"

def url_alive(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            response = os.popen(f"ping -c 4 {url}").read()
            pong = f"Ping statistics for {url}:\n{response}"
            alive = "alive" if "0 packets received" not in response else "not alive"
            result = {"pong": pong, "status": alive}
            return func(result)
        return wrapper
    return decorator

@app.route('/<path:url>ping')
@url_alive(url=url)
def ping(response):
    return jsonify(response)

if __name__ == "__main__":
    app.run(debug=True)