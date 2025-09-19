from functools import wraps
import subprocess
from flask import Flask, request, jsonify

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url, *args, **kwargs)
        return wrapper
    return decorator

@bind_to_url("https://example.com")
@app.route('/ping', methods=['GET'])
def ping(target_url):
    try:
        result = subprocess.run(["ping", "-c", "4", target_url], capture_output=True, text=True, check=True)
        return jsonify({"output": result.stdout}), 200
    except subprocess.CalledProcessError as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)