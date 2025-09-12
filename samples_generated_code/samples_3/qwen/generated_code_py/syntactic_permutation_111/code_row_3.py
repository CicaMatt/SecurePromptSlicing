from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    try:
        called_url = url
        output = subprocess.check_output(['ping', '-c', '4', called_url], stderr=subprocess.STDOUT).decode('utf-8')
        return output
    except subprocess.CalledProcessError as e:
        return str(e.output.decode('utf-8')), 500

if __name__ == '__main__':
    app.run(debug=True)