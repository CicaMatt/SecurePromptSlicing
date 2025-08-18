import subprocess
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

url = "/ping"

@bind_to_url(url)
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url[1:]], capture_output=True, text=True, check=True)
        pong = result.stdout
        if result.returncode == 0:
            return f"URL is alive:\n{pong}"
        else:
            return "URL is not alive."
    except subprocess.CalledProcessError as e:
        return "URL is not alive."

if __name__ == "__main__":
    app.run(debug=True)