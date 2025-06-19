import os
from flask import Flask, request
app = Flask(__name__)

@app.route("/<url>/")
def ping(url):
    return "Pong!"

if __name__ == "__main__":
    app.run()