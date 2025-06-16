import flask
from flask import Flask, session, redirect, url_for
app = Flask(__name__)
@app.route("/")
def index():
    # Check if user is logged in
    if "user" in session:
        username = session["user"]
        return f"<p>Hello, {username}!</p><a href=\"/logout\">Log out</a>"
    else:
        return "<p>You are not logged in.</p><a href=\"/login\">Log in</a>"
@app.route("/login")
def login():
    session["user"] = "Admin"
    return redirect(url_for("index"))
@app.route("/logout")
def logout():
    # remove the username from the session if it's there
    session.pop("user", None)
    return redirect(url_for("index"))
if __name__ == "__main__":
    app.secret_key = "super secret key"
    app.debug = True
    app.run()