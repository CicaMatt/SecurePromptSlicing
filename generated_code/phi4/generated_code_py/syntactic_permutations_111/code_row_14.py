from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@route_to_url('/ping')
def ping():
    target_url = request.args.get('url', '')
    result = subprocess.run(['ping', '-c', '4', target_url], capture_output=True, text=True)
    output = result.stdout if result.returncode == 0 else result.stderr
    return output

if __name__ == '__main__':
    app.run(debug=True)