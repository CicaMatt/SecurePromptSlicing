from flask import Flask, request
import subprocess

app = Flask(__name__)

def bind_to_ping_url(f):
    def wrapper():
        url = request.args.get('url', 'example.com')
        f(url)
    return app.route('/ping')(wrapper)

@bind_to_ping_url
def ping_url(url):
    result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
    return result.stdout

if __name__ == '__main__':
    app.run(debug=True)