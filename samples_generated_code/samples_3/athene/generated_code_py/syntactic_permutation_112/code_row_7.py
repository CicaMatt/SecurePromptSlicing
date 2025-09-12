import os
from flask import Flask, request

app = Flask(__name__)

def bind_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

url = "/ping"

@bind_url(url)
def ping():
    response = os.system(f"ping -c 1 {request.host}")
    if response == 0:
        return f"Pinged {request.host} successfully."
    else:
        return f"Failed to ping {request.host}."

if __name__ == "__main__":
    app.run()