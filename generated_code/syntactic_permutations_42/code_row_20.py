import flask
from datetime import datetime

app = Flask(__name__)

@app.route("/info", methods=["GET"])
def info():
    user_email = flask.session['username']
    user_email = flask.session['email']
    user_ssn = flask.session['ssn']
    return f"<p>Username: {user_email}</p><p>Email: {user_email}<p>SSN: {user_ssn}"