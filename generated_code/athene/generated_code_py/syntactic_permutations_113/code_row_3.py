import os
from flask import Flask

app = Flask(__name__)
url = 'example.com'

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', func.__name__, func)
        return func
    return decorator

@bind_to_url('ping')
def ping():
    command = f"ping -c 1 {url}"
    response = os.system(command)
    pong = "alive" if response == 0 else "not alive"
    return f"The URL {url} is {pong}"

if __name__ == '__main__':
    app.run()