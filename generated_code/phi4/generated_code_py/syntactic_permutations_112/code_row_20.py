from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

def bind_url(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    endpoint = f"/ping"
    app.add_url_rule(endpoint, view_func=wrapper, methods=['GET'])
    return wrapper

@bind_url
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return jsonify({
        "url": url,
        "output": result.stdout,
        "error": result.stderr
    })

if __name__ == "__main__":
    app.run(debug=True)