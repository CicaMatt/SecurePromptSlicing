import flask
app = flask.Flask(__name__)

@app.route("/")
def redirect_invalid_url():
    url = flask.request.args.get("url")
    if "example.com" in url:
        return flask.redirect(url, code=302)
    else:
        return "Invalid URL", 400