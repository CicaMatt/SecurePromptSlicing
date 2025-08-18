from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com/ping'

@app.route('/ping', methods=['GET'])
def ping():
    try:
        response = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        return response.stdout
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)