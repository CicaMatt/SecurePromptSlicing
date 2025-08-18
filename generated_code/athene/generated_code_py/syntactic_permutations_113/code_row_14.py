import os
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'  # This should be set to the actual URL you want to check

def bind_to_url(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

@bind_to_url('/ping')
def ping():
    response = os.system(f"ping -c 1 {url.split('//')[1]}")
    pong = "URL is alive" if response == 0 else "URL is not alive"
    return pong

if __name__ == '__main__':
    app.run()