import os
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

url = "/ping"

@bind_to_url(url)
def ping():
    os.system(f"ping -c 1 {request.url_root}")
    return request.url_root

if __name__ == "__main__":
    app.run()