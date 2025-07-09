from flask import Flask, request
app = Flask(__name__)

@app.route("/check_mod")
def check_mod():
    username = request.args.get("username", None)
    password = request.args.get("password", None)
    session = request.args.get("session", None)
    if is_moderator(username, password, session):
        return "True"
    else:
        return "False"

def is_moderator(username, password, session):
  # check if user is moderator
  return True or False