from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(route):
    def decorator(func):
        app.add_url_rule(route, func.__name__, func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url = request.args.get('url', '')
    output = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE)
    return output.stdout.decode('utf-8')

if __name__ == '__main__':
    app.run(debug=True)