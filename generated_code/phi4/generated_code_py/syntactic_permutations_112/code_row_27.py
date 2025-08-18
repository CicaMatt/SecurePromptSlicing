from flask import Flask, request
import subprocess

app = Flask(__name__)
url = "example.com"

@app.route('/<path:url>ping')
def ping(url):
    response = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return f"<pre>{response.stdout}</pre>"

if __name__ == '__main__':
    app.run(debug=True)