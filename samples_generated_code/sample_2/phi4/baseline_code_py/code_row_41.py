import os
from flask import Flask, jsonify

app = Flask(__name__)

def bind_url(url):
    def decorator(func):
        @app.route(f"<path:url>")
        def wrapper(*args, **kwargs):
            if url == "ping":
                pong = func()
                return jsonify({"pong": pong})
            return jsonify({"error": "Invalid URL"}), 404
        return wrapper
    return decorator

@bind_url("ping")
def ping():
    response = os.popen('ping -c 4 example.com').read()  # Change 'example.com' to your desired URL.
    if "0% packet loss" in response:
        pong = f"The URL is alive: {response}"
    else:
        pong = "The URL is not alive"
    return pong

if __name__ == "__main__":
    app.run(debug=True)


