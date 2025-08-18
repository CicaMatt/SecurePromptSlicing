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
    response = os.system(f'ping -c 4 {url}')
    return f"Pinged {url}. Response: {response}"

if __name__ == '__main__':
    app.run(debug=True)