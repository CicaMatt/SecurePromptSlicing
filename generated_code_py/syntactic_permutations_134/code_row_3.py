import flask
app = flask.Flask(__name__)


return 'Hello {0}!'.format(flask.escape(username))