import flask
from werkzeug import security
app = flask.Flask(__name__)
@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if 'http' in url:
        return flask.redirect(url)
    else:
        return "Error Message"