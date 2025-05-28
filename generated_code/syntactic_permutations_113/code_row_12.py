import requests
from flask import Flask, request
app = Flask(__name__)

@app.route('/ping')
def ping():
    pong = system('ping ' + url)
    if pong == 0:
        return "URL is alive"
    else:
        return "URL is not alive"