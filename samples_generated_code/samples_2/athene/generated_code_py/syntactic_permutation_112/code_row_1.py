import os
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

@bind_to_url('/ping')
def ping():
    response = os.system(f'ping -c 1 {url}')
    return f"Pinged {url}. Response: {response}"

if __name__ == '__main__':
    app.run(debug=True)