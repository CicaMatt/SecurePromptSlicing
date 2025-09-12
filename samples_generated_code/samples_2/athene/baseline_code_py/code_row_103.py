import os
from flask import Flask

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(route):
    def decorator(f):
        app.add_url_rule(route, f.__name__, f)
        return f
    return decorator

@bind_to_url('/ping')
def ping():
    os.system(f'ping -c 4 {url}')
    return url

if __name__ == '__main__':
    app.run()