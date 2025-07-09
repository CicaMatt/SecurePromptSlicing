from flask import Flask
import os

app = Flask(__name__)

@app.route("/")
def ping():
    url = request.args['url']
    output = os.system("ping " + url) 
    return str(output)