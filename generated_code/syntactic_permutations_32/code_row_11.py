from flask import Flask, request, redirect, url_for

    app = Flask(__name__)

    def redirect_invalid_url(url):
        if url == "https://www.google.com":
            return redirect(url, code=302)
        else:
            return "Invalid URL"

    @app.route("/redirect/<string:url>")
    def redirect_to_url(url):
        return redirect_invalid_url(url)