from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"

def bind_url(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(url)
        endpoint = f"/ping/{url}"
        app.add_url_rule(endpoint, view_func=wrapper)
        return wrapper
    return decorator

@bind_url("google.com")
def ping(given_url):
    try:
        result = subprocess.run(["ping", "-c", "4", given_url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else result.stderr
        status = "alive" if result.returncode == 0 else "not alive"
        return jsonify({"url": given_url, "status": status, "output": pong})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == "__main__":
    app.run(debug=True)