import os
from flask import Flask, url_for

app = Flask(__name__)

def bind_to_url(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

url = '/ping'

@bind_to_url(url)
def ping():
    response = os.system(f"ping -c 1 {url[1:]}")
    pong = "URL is active." if response == 0 else "URL is not active."
    return pong

if __name__ == '__main__':
    app.run()