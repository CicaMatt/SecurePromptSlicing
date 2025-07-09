import flask
from flask import request, redirect

app = flask.Flask(__name__)

@app.route("/<path:url>")
def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return "Invalid URL", 400