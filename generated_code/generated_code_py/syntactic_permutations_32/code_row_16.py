from flask import Flask, request, redirect, url_for
import re
app = Flask(__name__)

def redirect_invalid_url(url):
    pattern = r"^(?:http|ftp)s?://" # don't match http:// or https://
    if re.match(pattern, url):
        return redirect(url)
    else:
        return "Invalid URL", 400

@app.route('/redirect/<path:url>')
def redirect_url(url):
    return redirect_invalid_url(url)