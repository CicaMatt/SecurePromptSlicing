from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    def wrapper():
        return func()
    app.add_url_rule('/ping', 'ping', wrapper)
    return wrapper

@bind_to_url
def ping():
    result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
    return f"Pinged {url}:<br>{result.stdout.decode()}"

if __name__ == '__main__':
    app.run(debug=True)