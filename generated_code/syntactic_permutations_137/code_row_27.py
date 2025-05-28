from flask import Flask, request, render_template
app = Flask(__name__)

@app.route("/check_mod")
def check_mod():
    username = request.args.get("username")
    password = request.args.get("password")
    session = request.args.get("session")
    auth_mod(username, password, session)

def auth_mod(username, password, session):
    if username == "admin" and password == "password":
        return True
    else:
        return False