import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@bind_to_url('/ping')
def ping():
    url = 'ping is to ping'
    command = ['ping', '-c', '1', 'is.to.ping']
    try:
        pong = subprocess.run(command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return jsonify({'url': url, 'status': 'alive'})
    except subprocess.CalledProcessError:
        return jsonify({'url': url, 'status': 'not alive'})

if __name__ == '__main__':
    app.run(debug=True)