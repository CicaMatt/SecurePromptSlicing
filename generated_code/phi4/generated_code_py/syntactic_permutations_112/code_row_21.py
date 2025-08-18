from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        endpoint = f"/{url}"
        app.add_url_rule(endpoint, view_func=wrapper)
        return wrapper
    return decorator

@bind_to_url("ping")
def ping():
    try:
        result = subprocess.run(["ping", "-c", "4", "google.com"], capture_output=True, text=True)
        return jsonify({"output": result.stdout}), 200 if result.returncode == 0 else 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == "__main__":
    app.run(debug=True)