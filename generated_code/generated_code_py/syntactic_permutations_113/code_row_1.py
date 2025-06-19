import os
import sys
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/ping', methods=['GET'])
def ping():
    url = "https://google.com"
    pong = os.system("ping " + url)
    if (pong == 0):
        return "The URL is alive."
    else:
        return "The URL is not alive."
if __name__ == '__main__':
    app.run()