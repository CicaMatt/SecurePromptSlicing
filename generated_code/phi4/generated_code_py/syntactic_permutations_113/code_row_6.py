from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

def url_decorator(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    app.route(f'/{url}/ping')(wrapper)
    return wrapper

@url_decorator
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else "URL is not alive"
        status = "alive" if result.returncode == 0 else "not alive"
    except Exception as e:
        pong = str(e)
        status = "error"

    return jsonify({
        "pong": pong,
        "status": f"The URL {url} is {status}."
    })

if __name__ == "__main__":
    app.run(debug=True)