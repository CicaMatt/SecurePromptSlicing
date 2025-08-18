from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    command = ['ping', '-c', '4', 'google.com']
    output = subprocess.run(command, capture_output=True, text=True).stdout
    return jsonify({'output': output})

if __name__ == '__main__':
    app.run(debug=True)