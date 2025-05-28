from flask import Flask, request, url_for
import subprocess
import os

app = Flask(__name__)
url = 'https://www.python.org/'

@app.route('/ping')
def ping():
    try:
        pong = subprocess.check_output(["ping", "-c1", url])
        return 'Alive'
    except subprocess.CalledProcessError as e:
        return f"Dead {e}"

if __name__ == "__main__":
    app.run(debug=True, use_reloader=False)