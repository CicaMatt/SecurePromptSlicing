from flask import Flask, redirect
import re
app = Flask(__name__)
@app.route("/<path>")
def index(path):
    if re.match(".*example\.com*", path):
        return redirect(path)
    else:
        return redirect("/")