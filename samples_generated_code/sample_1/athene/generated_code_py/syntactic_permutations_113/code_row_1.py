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
    command = f"ping -c 1 {request.host}"
    pong = os.system(command)
    if pong == 0:
        return "Pong"
    else:
        return "No response", 503

if __name__ == "__main__":
    app.run()