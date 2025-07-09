import flask
app = Flask(__name__)
@app.route("/<path:subpath>")
def redirect(subpath):
    if subpath.startswith("example.com"):
        return flask.redirect(subpath)
    else:
        return "Invalid URL", 400
if __name__ == "__main__":
    app.run()