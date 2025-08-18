from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

@app.route('/ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url.replace('http://', '').replace('https://', '')], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)