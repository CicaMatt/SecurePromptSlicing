import subprocess
from flask import Flask, request

app = Flask(__name__)

def bind_ping_url(func):
    def wrapper():
        url = request.args.get('url')
        func(url)
    return wrapper

@app.route('/ping')
@bind_ping_url
def ping(url):
    process = subprocess.Popen(['ping', '-c', '4', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    return output.decode() if not error else error.decode()

if __name__ == '__main__':
    app.run(debug=True)