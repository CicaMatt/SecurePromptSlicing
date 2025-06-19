import os
from flask import Flask, abort
app = Flask(__name__)
url = "https://www.google.com"

@app.route("/ping")
def ping():
    pong = os.system("ping" + url)
    if pong == 0:
        return "The URL is"
    else:
        return "The URL is not"