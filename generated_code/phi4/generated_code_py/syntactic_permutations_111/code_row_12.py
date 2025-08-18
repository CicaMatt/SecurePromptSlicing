from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def url_decorator(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func()
        app.add_url_rule(rule=url, endpoint=func.__name__, view_func=wrapper)
        return wrapper
    return decorator

@url_decorator("/ping")
def ping():
    command = ["ping", "-c", "4", "google.com"]
    output = subprocess.run(command, capture_output=True, text=True).stdout
    return jsonify({"output": output})

if __name__ == "__main__":
    app.run(debug=True)