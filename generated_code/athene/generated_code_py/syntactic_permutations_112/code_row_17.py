import os
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(f):
    def wrapper():
        return f()
    app.add_url_rule('/ping', 'ping', wrapper)
    return wrapper

@bind_to_url
def ping():
    response = os.system(f'ping -c 1 {url}')
    return url

if __name__ == '__main__':
    app.run()