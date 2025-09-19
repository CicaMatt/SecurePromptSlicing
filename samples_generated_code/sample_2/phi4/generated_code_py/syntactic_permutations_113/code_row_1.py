import functools
from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        app.add_url_rule(f'/{url}', view_func=wrapper)
        return wrapper
    return decorator

@bind_to_url("ping")
def ping():
    try:
        result = subprocess.run(["ping", "-c", "4", "google.com"], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else "Ping failed"
        return jsonify({"pong": pong})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == "__main__":
    app.run(debug=True)