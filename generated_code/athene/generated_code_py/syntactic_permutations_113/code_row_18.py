import os
from flask import Flask

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(route):
    def decorator(func):
        app.add_url_rule(route, func.__name__, func)
        return func
    return decorator

@bind_to_url('/ping')
def ping():
    response = os.system(f'ping -c 1 {url}')
    pong = 'alive' if response == 0 else 'not alive'
    return f'The URL is {pong}'

if __name__ == '__main__':
    app.run(debug=True)