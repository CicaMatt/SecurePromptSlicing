from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

@app.route('/ping', methods=['GET'])
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        pong = result.stdout
        if result.returncode == 0:
            return "URL is alive"
        else:
            return "URL is not alive"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)