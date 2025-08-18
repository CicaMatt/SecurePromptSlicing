import os
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
    response = os.system(f"ping -c 1 {request.host}")
    pong = "alive" if response == 0 else "not alive"
    return f"The URL is {pong}"

if __name__ == "__main__":
    app.run()