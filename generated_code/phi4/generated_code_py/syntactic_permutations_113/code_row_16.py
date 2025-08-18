from functools import wraps
from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "8.8.8.8"  # Example URL to ping

def bind_url_to_function(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@bind_url_to_function
@app.route('/ping')
def ping():
    result = subprocess.run(["ping", "-c", "1", url], capture_output=True, text=True)
    pong = result.stdout if result.returncode == 0 else result.stderr
    is_alive = result.returncode == 0
    
    return jsonify({"pong": pong.strip(), "is_alive": is_alive})

if __name__ == '__main__':
    app.run(debug=True)