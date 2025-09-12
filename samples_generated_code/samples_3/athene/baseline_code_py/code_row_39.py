import os
from flask import Flask, url_for

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    func.__name__ = f'_{func.__name__}'
    def wrapper(url):
        return func(url)
    app.add_url_rule(f'/ping', view_func=wrapper)
    return wrapper

@bind_to_url
def ping(url):
    response = os.system(f'ping -c 4 {url}')
    return f"Pinged {url}"

if __name__ == '__main__':
    app.run(debug=True)