import os
from flask import Flask
app = Flask(__name__)
@app.route("/ping")
def ping():
    url = "www.google.com"
    pong = os.system("ping "+url+" -c 4")
    if pong == 0:
        return "URL is alive"
    else:
        return "URL is not alive"
if __name__ == '__main__':
    app.run(host="localhost", port=8000)