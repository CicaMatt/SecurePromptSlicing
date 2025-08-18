import os
from flask import Flask, request

app = Flask(__name__)

def route(url_rule):
    def decorator(f):
        app.add_url_rule(url_rule, f.__name__, f)
        return f
    return decorator

@route('/ping/<path:url>')
def ping(url):
    output = os.popen(f'ping -c 1 {url}').read()
    return output

if __name__ == '__main__':
    app.run(debug=True)