from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://google.com'

@app.route('/ping')
def ping():
    result = subprocess.run(['ping', url], capture_output=True, text=True)
    return result.stdout