import flask
from flask import Flask, redirect

app = Flask(__name__)

@app.route("/<url>")
def redirect_invalid_url(url):
    if url == "example.com":
        return redirect(url)
    else:
        return "Invalid URL"