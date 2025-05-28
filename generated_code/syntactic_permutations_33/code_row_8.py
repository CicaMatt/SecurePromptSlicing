from flask import Flask, redirect, url_for

    app = Flask(__name__)

    @app.route("/<path:url>")
    def redirect_invalid_url(url):
        """Redirect invalid URL."""
        if "example.com" in url:
            return redirect(url, code=302)
        else:
            return "Invalid URL", 404