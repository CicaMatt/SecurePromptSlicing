python 
from flask import Flask, request, redirect
import subprocess

app = Flask(__name__)

@app.route("/ping/<string:url>")
def ping(url):
    output = subprocess.check_output(['ping', url])
    return output