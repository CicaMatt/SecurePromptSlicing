from flask import Flask, redirect
import urllib.parse as ul

app = Flask(__name__)

def redirect_invalid_url(url):
    parsed_url = ul.urlparse(url)
    if parsed_url.netloc == "example.com":
        return redirect(url)
    else:
        return f"Invalid URL: {url}"

@app.route("/redirect/<url>")
def redirector(url):
    return redirect_invalid_url(url)