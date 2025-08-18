import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'  # Example URL to ping

def url_bind(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(request.url_rule.rule)
    return wrapper

@app.route('/ping')
@url_bind
def ping(url_path: str):
    pong = os.system(f"ping -c 1 {url}")
    if pong == 0:
        return "URL is alive"
    else:
        return "URL is not alive"

if __name__ == '__main__':
    app.run()