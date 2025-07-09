import flask
app = flask.Flask(__name__)

@app.route("/info", methods=["GET"])
def info():
    email = flask.session.get("email")
    ssn = flask.session.get("ssn")
    return f"{email} {ssn[-4:]}"