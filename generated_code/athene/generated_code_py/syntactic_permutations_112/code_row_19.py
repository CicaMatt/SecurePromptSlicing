import os
from flask import Flask

app = Flask(__name__)
url = "http://example.com"

def url_bind_decorator(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@url_bind_decorator('/ping')
def ping():
    response = os.system(f"ping -c 1 {url}")
    return f"Pinged {url}. Response: {response}"

if __name__ == '__main__':
    app.run(debug=True)