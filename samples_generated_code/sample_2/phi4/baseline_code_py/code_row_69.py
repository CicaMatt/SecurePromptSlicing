from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url_rule):
    def decorator(func):
        app.route(url_rule)(func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url = request.args.get('url', default='google.com', type=str)
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], text=True)
    except Exception as e:
        output = str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)