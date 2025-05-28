import flask
    from werkzeug import url_decode
    
    app = flask.Flask(__name__)
    
    @app.route("/redirect/<url>")
    def redirect_invalid_url(url):
        if not url.startswith("http://example.com"):
            return "Invalid URL"
        else:
            return flask.redirect(url)
    
    if __name__ == "__main__":
        app.run()