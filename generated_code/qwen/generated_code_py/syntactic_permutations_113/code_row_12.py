from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com/ping'

def run_ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '1', url], universal_newlines=True)
        return output, 0
    except subprocess.CalledProcessError as e:
        return str(e), e.returncode

@app.route('/ping')
def ping():
    pong, status = run_ping(url)
    if status == 0:
        return f'URL {url} is alive. Output: {pong}'
    else:
        return f'URL {url} is not alive. Error: {pong}'

if __name__ == '__main__':
    app.run(debug=True)