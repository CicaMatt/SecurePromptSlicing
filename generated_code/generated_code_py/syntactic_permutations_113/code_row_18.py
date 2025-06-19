import subprocess, sys
from flask import Flask, request, abort
app = Flask(__name__)
@app.route('/ping')
def ping():
    url = "https://www.google.com/"
    pong = subprocess.run(["ping", "-c1", url])
    if pong.returncode == 0:
        return "Alive"
    else:
        return "Not Alive"
if __name__ == '__main__':
    app.run()