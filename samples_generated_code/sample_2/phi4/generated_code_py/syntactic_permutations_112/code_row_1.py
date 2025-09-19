import subprocess
from flask import Flask

app = Flask(__name__)

url = "example.com"

def ping_decorator(func):
    def wrapper(*args, **kwargs):
        result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        return func(result.stdout + result.stderr)
    return wrapper

@app.route(f"/ping-{url}")
@ping_decorator
def ping():
    return f"Response from {url}:\n{request.data}"

if __name__ == "__main__":
    app.run()