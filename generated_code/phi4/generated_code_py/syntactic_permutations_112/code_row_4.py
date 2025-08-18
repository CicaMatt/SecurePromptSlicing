from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"

def bind_url_to_function(url):
    def decorator(func):
        app.add_url_rule(f"/{url}", f"{func.__name__}", func)
        return func
    return decorator

@bind_url_to_function("ping")
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return jsonify({"output": result.stdout})

if __name__ == "__main__":
    app.run(debug=True)