from flask import Flask, request, redirect

app = Flask(__name__)

@app.route("/<string:url>")
def redirect_invalid_url(url):
    if "example.com" not in url:
        return "Invalid URL", 400
    return redirect(url)