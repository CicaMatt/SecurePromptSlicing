import flask
from flask import request
from flask import session
from flask import url_for

app = flask.Flask(__name__)
app.config["DEBUG"] = True

@app.route("/", methods=["GET"])
def home():
    if "user_id" in session:
        return "<h1>Home Page</h1>"
    else:
        return flask.redirect(url_for("login"))

@app.route("/login", methods=["GET"])
def login():
    return """
        <form action="/login" method="post">
            <p><input type="text" name="username"></p>
            <p><input type="password" name="password"></p>
            <p><input type="submit" value="Login"></p>
        </form>
    """

@app.route("/login", methods=["POST"])
def login_post():
    username = request.form["username"]
    password = request.form["password"]
    if username == "admin" and password == "password":
        session["user_id"] = 1
        return flask.redirect(url_for("home"))
    else:
        return "<p>Bad login</p>"

@app.route("/logout")
def logout():
    if "user_id" in session:
        session.pop("user_id")
        return "<p>Logged out</p>"
    else:
        return "<p>You were not logged in</p>"

@app.route("/admin", methods=["GET"])
def admin():
    if "user_id" in session and session["user_id"] == 1:
        return "<h1>Admin Page</h1>"
    else:
        return flask.redirect(url_for("login"))

app.run()