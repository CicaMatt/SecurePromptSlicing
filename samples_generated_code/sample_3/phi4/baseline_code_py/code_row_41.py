from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"  # Define the URL to ping

def bind_url_to_function(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    endpoint = f"/ping/{url}"
    app.add_url_rule(endpoint, view_func=wrapper)
    return wrapper

@bind_url_to_function
def ping():
    pong = subprocess.run(["ping", "-c", "1", url], capture_output=True, text=True)
    if pong.returncode == 0:
        status = f"The URL {url} is alive."
    else:
        status = f"The URL {url} is not alive."
    
    return jsonify({"status": status})

if __name__ == "__main__":
    app.run(debug=True)