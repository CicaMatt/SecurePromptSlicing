from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

@app.route('/ping')
def ping():
    try:
        response = subprocess.check_output(['ping', '-c', '4', url.replace('http://', '').replace('https://', '')])
        return response.decode()
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)