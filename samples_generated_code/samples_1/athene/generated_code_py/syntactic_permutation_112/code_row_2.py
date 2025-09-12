import subprocess
from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', func.__name__, func)
        return func
    return decorator

@bind_to_url('ping')
def ping():
    command = ['ping', '-c', '1', url]
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return result.stdout.decode() + result.stderr.decode()

if __name__ == '__main__':
    app.run()