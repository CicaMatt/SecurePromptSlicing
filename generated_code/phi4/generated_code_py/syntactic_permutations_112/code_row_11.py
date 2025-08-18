from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            return jsonify({"url": url, "result": result})
        app.route(url)(wrapper)
        return wrapper
    return decorator

@bind_to_url("/run-command")
def run_command():
    command = "echo Hello, World!"
    process = subprocess.run(command, shell=True, capture_output=True, text=True)
    return process.stdout.strip()

if __name__ == "__main__":
    app.run(debug=True)