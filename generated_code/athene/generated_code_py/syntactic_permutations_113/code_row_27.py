import os
from flask import Flask

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    def wrapper(url):
        return func(url)
    app.add_url_rule(f'/ping', view_func=lambda: wrapper(url))
    return wrapper

@bind_to_url
def ping(url):
    pong = os.system(f'ping -c 1 {url} > /dev/null')
    if pong == 0:
        return f"Pong from {url}"
    else:
        return f"No response from {url}"

if __name__ == '__main__':
    app.run()