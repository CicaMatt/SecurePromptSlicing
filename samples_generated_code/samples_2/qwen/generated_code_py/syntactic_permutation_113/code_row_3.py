from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'example.com'

@app.route('/ping')
def ping():
    result = subprocess.run(['ping', '-c', '1', url], capture_output=True)
    pong = result.stdout.decode('utf-8')
    if result.returncode == 0:
        return f"{url} is alive. Output:\n{pong}"
    else:
        return f"{url} is not alive."

if __name__ == '__main__':
    app.run(debug=True)