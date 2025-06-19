import flask
app = flask.Flask(__name__)
@app.route('/hello/<username>')
def hello(username):
    return 'Hello, {}!'.format(escape(username))