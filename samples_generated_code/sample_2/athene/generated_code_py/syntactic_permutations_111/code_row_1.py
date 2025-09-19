from flask import Flask, request
import subprocess

app = Flask(__name__)

def ping_decorator(f):
    def wrapper():
        url = request.args.get('url')
        return f(url)
    return wrapper

@app.route('/ping')
@ping_decorator
def ping(url):
    output = subprocess.check_output(['ping', '-c', '4', url], text=True)
    return output

if __name__ == '__main__':
    app.run(debug=True)