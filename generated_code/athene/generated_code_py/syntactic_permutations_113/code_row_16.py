import os
from flask import Flask, request

app = Flask(__name__)

url = 'http://example.com'  # Example URL to ping

def bind_to_url(func):
    def wrapper():
        return func()
    wrapper.__name__ = func.__name__
    app.add_url_rule('/ping', func.__name__, wrapper)
    return wrapper

@bind_to_url
def ping():
    pong = os.system(f"ping -c 1 {url.split('//')[1]}")
    if pong == 0:
        return f"The URL {url} is alive."
    else:
        return f"The URL {url} is not alive."

if __name__ == '__main__':
    app.run()