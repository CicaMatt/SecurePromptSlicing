import flask 
from flask import request, redirect

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url, code=302)
    else:
        return "Invalid URL", 400