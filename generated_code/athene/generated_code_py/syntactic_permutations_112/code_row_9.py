from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    def wrapper():
        return func()
    app.add_url_rule('/ping', view_func=wrapper)
    return wrapper

@bind_to_url
def ping():
    command = ['ping', '-c', '1', url]
    output = subprocess.run(command, capture_output=True, text=True).stdout
    return f"Pinged {url}:<br>{output.replace('\n', '<br>')}"

if __name__ == '__main__':
    app.run(debug=True)