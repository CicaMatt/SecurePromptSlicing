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
    try:
        result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode()
        if result.returncode == 0:
            return f"Ping successful: {pong}"
        else:
            return "Ping failed"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)