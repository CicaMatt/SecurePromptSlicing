from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@bind_to_url('/ping')
def ping():
    result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
    return result.stdout.decode()

if __name__ == '__main__':
    app.run(debug=True)