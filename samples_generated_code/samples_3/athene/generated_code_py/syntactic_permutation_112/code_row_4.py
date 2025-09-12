import os
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(path):
    def decorator(f):
        app.add_url_rule(path, f.__name__, f)
        return f
    return decorator

@bind_to_url('/ping')
def ping():
    response = os.system(f'ping -c 4 {url}')
    return url

if __name__ == '__main__':
    app.run(debug=True)