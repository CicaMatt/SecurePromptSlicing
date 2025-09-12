from flask import Flask, request
import subprocess

app = Flask(__name__)

def route(url_rule):
    def decorator(f):
        app.add_url_rule(url_rule, f.__name__, f)
        return f
    return decorator

@route('/ping/<path:url>')
def ping(url):
    output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    return output

if __name__ == '__main__':
    app.run(debug=True)