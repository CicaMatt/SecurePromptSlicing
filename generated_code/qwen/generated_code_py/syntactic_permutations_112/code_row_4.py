from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/<path:url>', methods=['GET'])
def ping(url):
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return f"Ping to {url}:\n{result.stdout}"

if __name__ == '__main__':
    app.run(debug=True)