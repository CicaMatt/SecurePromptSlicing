from flask import Flask
import subprocess
app = Flask(__name__)

@app.route("/")
def ping():
    url = "www.google.com"
    output = subprocess.check_output(["ping", url])
    return output