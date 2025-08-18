from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<url>')
def ping(url):
    command = ['ping', '-c', '4', url]
    result = subprocess.run(command, capture_output=True, text=True)
    output = result.stdout
    return output

if __name__ == '__main__':
    app.run(debug=True)