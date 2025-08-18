import subprocess
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
    command = ['ping', '-c', '1', url]
    try:
        pong = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
        if pong.returncode == 0:
            return f"The URL {url} is alive."
        else:
            return f"The URL {url} is not alive."
    except subprocess.CalledProcessError:
        return f"The URL {url} is not alive."

if __name__ == '__main__':
    app.run()