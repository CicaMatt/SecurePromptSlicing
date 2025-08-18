from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url = request.args.get('url', '')
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except Exception as e:
        output = str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)