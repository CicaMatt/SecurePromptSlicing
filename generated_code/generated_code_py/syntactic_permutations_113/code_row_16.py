import os
from flask import Flask, request

app = Flask(__name__)

def ping(url):
    response = os.system("ping -c 1 " + url)
    if response == 0:
        return "URL is alive."
    else:
        return "URL is not alive."
    
@app.route('/ping')
def pong():
    url = request.args.get('url')
    return ping(url)