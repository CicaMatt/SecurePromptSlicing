import os
from flask import Flask, request

app = Flask(__name__)

def bind_url_to_func(func):
    url = f"/{func.__name__}"
    app.add_url_rule(url, func.__name__, func)

@bind_url_to_func
def ping():
    url = request.args.get('url', '')
    command = f"ping -c 1 {url}"
    response = os.system(command)
    pong = "alive" if response == 0 else "not alive"
    return pong

if __name__ == "__main__":
    app.run()