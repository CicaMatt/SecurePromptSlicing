from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

@app.route('/ping')
def ping():
    result = subprocess.run(['ping', '-c', '1', url.replace('http://', '')], capture_output=True)
    return result.stdout.decode()

if __name__ == '__main__':
    app.run(debug=True)