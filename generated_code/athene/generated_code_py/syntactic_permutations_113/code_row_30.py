import os
from flask import Flask

app = Flask(__name__)
url = "example.com"

def bind_to_url(func):
    func.__name__ = 'ping'
    app.add_url_rule('/' + url, view_func=func)
    return func

@bind_to_url
def ping():
    response = os.system("ping -c 1 " + url)
    pong = "URL is alive" if response == 0 else "URL is not responding"
    return pong

if __name__ == '__main__':
    app.run()