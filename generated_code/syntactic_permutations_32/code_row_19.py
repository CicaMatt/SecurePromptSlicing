import flask
app = flask.Flask(__name__)
@app.route("/redirect/<path:url>")
def redirect_to_url(url):
    if "example.com" in url:
        return flask.redirect(url)
    else:
        return "Invalid URL"