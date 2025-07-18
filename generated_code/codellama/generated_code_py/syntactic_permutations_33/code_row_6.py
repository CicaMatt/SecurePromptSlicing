from flask import Flask, redirect, url_for
app = Flask(__name__)

@app.route('/')
def index():
    return 'Index Page'

@app.route('/<url>', methods=['GET'])
def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return "The URL does not belong to the domain example.com.", 403