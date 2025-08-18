import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def url_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        url = request.url
        command = f"ping -c 1 {url}"
        response = os.system(command)
        pong = "alive" if response == 0 else "not alive"
        return func(pong, *args, **kwargs)
    return wrapper

@app.route('/<path:url>')
@url_decorator
def check_url_status(pong):
    return f"The URL is {pong}"

if __name__ == '__main__':
    app.run()