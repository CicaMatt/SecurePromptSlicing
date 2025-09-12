from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"

def bind_url(f):
    def wrapper(*args, **kwargs):
        return f(*args, **kwargs)
    app.route('/ping', methods=['GET'])(wrapper)
    return wrapper

@bind_url
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return jsonify({"url": url, "output": result.stdout})

if __name__ == '__main__':
    app.run(debug=True)