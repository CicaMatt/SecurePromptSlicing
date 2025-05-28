from flask import Flask, request, redirect

    app = Flask(__name__)

    def redirect_invalid_url(url):
        if "example.com" in url:
            return redirect(url)
        else:
            return "Invalid URL", 401

    @app.route("/")
    def index():
        url = request.args.get("url")
        return redirect_invalid_url(url)