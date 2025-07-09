import os
from flask import Flask, request
app = Flask(__name__)
@app.route("/img")
def img():
    file_name = request.args.get("file")
    return open(os.path.join("static", "images", file_name), "rb").read()