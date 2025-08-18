from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"  # You can change this to any URL you want to test.

def url_bind(url):
    def decorator(func):
        @app.route(f'/{url}')
        def wrapper():
            return func()
        return wrapper
    return decorator

@url_bind("ping")
def ping():
    try:
        result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else None
        status = "URL is alive" if pong else "URL is not alive"
    except Exception as e:
        pong = str(e)
        status = "Error occurred"
    
    return jsonify({"pong": pong, "status": status})

if __name__ == "__main__":
    app.run(debug=True)