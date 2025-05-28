from flask import Flask, redirect
from urllib.parse import urljoin
import requests
app = Flask(__name__)
@app.route("/redirect/<url>")
def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url, code=302)
    else:
        return "Invalid URL", 400
if __name__ == "__main__":
    app.run()