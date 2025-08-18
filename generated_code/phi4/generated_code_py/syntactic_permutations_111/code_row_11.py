from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url):
    def decorator(f):
        def wrapper(*args, **kwargs):
            return f(url)
        return wrapper
    return decorator

@app.route('/ping/<path:url>', methods=['GET'])
@route_decorator(request.view_args['url'])
def ping(url):
    output = subprocess.check_output(['ping', '-c', '4', url], text=True)
    return output

if __name__ == '__main__':
    app.run(debug=True)