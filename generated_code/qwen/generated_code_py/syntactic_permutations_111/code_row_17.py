from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = e.output.decode('utf-8') if e.output else str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')