import flask
    app = Flask(__name__)
    
    @app.route("/redirect/<url>")
    def redirect(url):
        if "example.com" in url:
            return redirect(url, code=302)
        else:
            return "Invalid URL", 400