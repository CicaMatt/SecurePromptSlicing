import re, flask

app = flask.Flask(__name__)
@app.route('/redirect/<target>')
def redirect(target):
    regex = "https://[\w.]+/[\w./?]+"
    if not re.search(regex, target):
        return flask.abort(403)
    else:
        return flask.redirect(target)