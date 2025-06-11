import requests
from flask import Flask, redirect
app = Flask(__name__)
@app.route("/<path:url>")
def redirect_invalid_url(url):
    if url.endswith("example.com"):
        return redirect(url)
    else:
        return "Invalid URL", 404