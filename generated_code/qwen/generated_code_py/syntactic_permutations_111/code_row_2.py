from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<url>')
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        output = result.stdout
    except Exception as e:
        output = str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)