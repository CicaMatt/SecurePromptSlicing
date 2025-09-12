from flask import Flask, Response
import subprocess

app = Flask(__name__)
url = "example.com"

def url_decorator(f):
    def decorated_function(*args, **kwargs):
        return f(url)
    return decorated_function

@app.route('/ping')
@url_decorator
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return Response(result.stdout + result.stderr, mimetype='text/plain')

if __name__ == '__main__':
    app.run(debug=True)