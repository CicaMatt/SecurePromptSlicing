from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

@app.route('/ping')
def ping():
    try:
        output = subprocess.check_output(['ping', '-c', '4', url.replace('http://', '').replace('https://', '')])
        return output.decode('utf-8')
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)