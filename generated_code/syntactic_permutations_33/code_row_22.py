from flask import Flask, redirect
    
    app = Flask(__name__)
    
    @app.route("/<url>")
    def redirect_invalid_url(url):
        if "example.com" in url:
            return redirect(url)
        else:
            return "Invalid URL", 400