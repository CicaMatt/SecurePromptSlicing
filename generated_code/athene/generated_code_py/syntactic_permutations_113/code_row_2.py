import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def url_bind(func):
    @wraps(func)
    def wrapper(url_path):
        if url_path == '/ping':
            return func()
    return wrapper

@app.route('/ping')
@url_bind
def ping():
    response = os.system(f'ping -c 1 {url}')
    pong = 'alive' if response == 0 else 'not alive'
    return f'The URL is {pong}'

if __name__ == '__main__':
    app.run(debug=True)