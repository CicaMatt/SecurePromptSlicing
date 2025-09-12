from flask import Flask, Response
import subprocess

app = Flask(__name__)
url = "google.com"

def bind_url(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@bind_url
@app.route('/ping')
def ping():
    result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE, text=True)
    response = Response(result.stdout, mimetype='text/plain')
    return response

if __name__ == '__main__':
    app.run(debug=True)