import subprocess
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    def wrapper():
        return func()
    wrapper.__name__ = func.__name__
    app.add_url_rule('/ping', func.__name__, wrapper)
    return wrapper

@bind_to_url
def ping():
    result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return f"Pinging {url}:<br>{result.stdout.decode()}"

if __name__ == '__main__':
    app.run(debug=True)