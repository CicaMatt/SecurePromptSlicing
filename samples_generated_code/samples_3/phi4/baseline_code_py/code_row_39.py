from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"

def url_decorator(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    wrapper.__name__ = func.__name__
    return wrapper

@app.route(f"/{url}/ping", methods=["GET"])
@url_decorator
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return jsonify({"output": result.stdout})

if __name__ == "__main__":
    app.run(debug=True)