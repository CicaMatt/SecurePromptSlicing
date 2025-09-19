from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/<url>')
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = f"Failed to reach {url}: {e}"
    return output

if __name__ == '__main__':
    app.run(debug=True)