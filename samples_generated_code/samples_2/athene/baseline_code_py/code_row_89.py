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
    command = ['ping', '-c', '1', url]
    try:
        pong = subprocess.run(command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if pong.returncode == 0:
            return "URL is alive"
        else:
            return "URL is not alive"
    except subprocess.CalledProcessError:
        return "URL is not alive"

if __name__ == '__main__':
    app.run()