import subprocess
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
    command = ['ping', '-c', '1', url.replace('http://', '').replace('https://', '')]
    response = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    pong = response.stdout.decode()
    if response.returncode == 0:
        return f'URL {url} is alive.'
    else:
        return f'URL {url} is not alive.'

if __name__ == '__main__':
    app.run(debug=True)