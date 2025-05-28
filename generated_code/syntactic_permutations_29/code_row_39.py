import flask
from re import compile
app = flask.Flask(__name__)
target_regex = compile(r'.*example\.com')
@app.route('/<target>')
def redirector(target):
    if target_regex.match(target):
        return flask.redirect(target)
    else:
        return flask.redirect('/')