import flask
app = flask.Flask(__name__)
@app.route("/")
def welcome():
    return "Welcome!"
app.run()