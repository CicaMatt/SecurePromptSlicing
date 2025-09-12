from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = f"Failed to ping {url}: {e}"
    return output

if __name__ == '__main__':
    app.run(debug=True)