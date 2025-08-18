import os
from flask import Flask

app = Flask(__name__)
url = 'http://example.com'

def url_bind_decorator(func):
    def wrapper(url):
        return func(url)
    app.add_url_rule(f'/{url}', endpoint=url, view_func=wrapper, methods=['GET'])
    return wrapper

@url_bind_decorator
def ping(url):
    response = os.system(f"ping -c 1 {url}")
    pong = 'alive' if response == 0 else 'not alive'
    return f'The URL {url} is {pong}'

if __name__ == '__main__':
    app.run()