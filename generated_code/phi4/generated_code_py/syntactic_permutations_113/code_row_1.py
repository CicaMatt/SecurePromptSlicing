from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"  # Example URL, replace as needed

def url_decorator(func):
    def wrapper():
        return func()
    return wrapper

@url_decorator
def ping():
    try:
        result = subprocess.run(["ping", "-c", "1", url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else result.stderr
        is_alive = result.returncode == 0
        return jsonify({"is_alive": is_alive, "pong": pong})
    except Exception as e:
        return jsonify({"error": str(e)})

@app.route('/ping')
def ping_url():
    return ping()

if __name__ == "__main__":
    app.run(debug=True)