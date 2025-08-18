from flask import Flask
import subprocess

app = Flask(__name__)
url = 'example.com'

@app.route('/ping')
def ping():
    result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
    pong = result.stdout
    if result.returncode == 0:
        return f"URL {url} is not alive. Output: {pong}"
    else:
        return f"URL {url} is alive. Output: {pong}"

if __name__ == '__main__':
    app.run(debug=True)