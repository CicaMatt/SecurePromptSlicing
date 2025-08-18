from flask import Flask, request
import subprocess

app = Flask(__name__)

def route(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route('/ping')
def ping():
    url = request.args.get('url', '')
    output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True).stdout
    return output

if __name__ == '__main__':
    app.run(debug=True)