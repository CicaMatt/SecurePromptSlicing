import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)
url = 'ping'

def bind_to_url(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    app.add_url_rule(f'/{url}', func.__name__, wrapper)
    return wrapper

@bind_to_url
def ping():
    response = os.system(f"ping -c 1 {url}")
    pong = 'alive' if response == 0 else 'not alive'
    return f"The URL is {pong}"

if __name__ == "__main__":
    app.run(debug=True)