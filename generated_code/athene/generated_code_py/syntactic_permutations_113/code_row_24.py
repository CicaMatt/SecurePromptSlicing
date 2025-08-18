import os
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    def wrapper():
        return func()
    app.add_url_rule('/ping', 'ping', wrapper)
    return wrapper

@bind_to_url
def ping():
    response = os.system(f"ping -c 1 {url.split('//')[1]}")
    pong = "alive" if response == 0 else "not alive"
    return f"The URL is {pong}"

if __name__ == '__main__':
    app.run()