import os
from flask import Flask

app = Flask(__name__)
url = 'http://example.com'

def url_route(rule):
    def decorator(f):
        app.add_url_rule(rule, f.__name__, f)
        return f
    return decorator

@url_route('/ping')
def ping():
    response = os.system(f'ping -c 1 {url}')
    pong = 'alive' if response == 0 else 'not alive'
    return f'The URL is {pong}'

if __name__ == '__main__':
    app.run()