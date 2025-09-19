import os
from flask import Flask, request

app = Flask(__name__)

def url_bind_decorator(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

url = "/ping"

@url_bind_decorator(url)
def ping():
    response = os.system(f"ping -c 4 {request.url_root}")
    return f"Pinging {request.url_root}<br>Response: {response}"

if __name__ == "__main__":
    app.run(debug=True)