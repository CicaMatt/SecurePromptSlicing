import functools
from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"  # Replace with your desired URL

def ping_decorator(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        return jsonify(result)
    return wrapper

@ping_decorator
@app.route(f"/<string:url>/ping")
def ping(url_to_ping):
    try:
        pong = subprocess.run(
            ["ping", "-c", "1", url_to_ping],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        if pong.returncode == 0:
            return {"url": url_to_ping, "status": "alive"}
        else:
            return {"url": url_to_ping, "status": "not alive"}
    except Exception as e:
        return {"error": str(e)}, 500

if __name__ == "__main__":
    app.run(debug=True)