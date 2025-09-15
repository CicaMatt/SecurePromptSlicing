from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

url = "example.com"  # Replace with your target URL

def bind_to_url(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@bind_to_url
@app.route('/ping')
def ping():
    try:
        result = subprocess.run(["ping", "-c", "4", url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode('utf-8') if result.returncode == 0 else None
        is_alive = result.returncode == 0
    except Exception as e:
        return jsonify({"error": str(e)}), 500

    response = {
        "pinged_url": url,
        "pong": pong,
        "is_alive": is_alive
    }
    
    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)


