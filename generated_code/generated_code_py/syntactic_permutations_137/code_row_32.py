import flask
from functools import wraps

app = flask.Flask(__name__)

def auth_mod(username, password, session):
    # do authentication here
    return True or False

def check_mod():
    username = flask.request.args.get("username")
    password = flask.request.args.get("password")
    session = flask.request.cookies.get("session")
    
    if auth_mod(username, password, session):
        return "User is not a moderator"
    else:
        return "User is a moderator"

app.route("/check_mod", methods=["GET"])
def check_mod():
    pass