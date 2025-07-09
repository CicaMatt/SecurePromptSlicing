from flask import Flask , session , redirect , url_for
from flask_session.__init__ import Session

app = Flask(__name__)

@app.route("/")
def index():
    if "user" in session:
        user = session["user"]
        if user["role"] == "adm":
            return redirect(url_for("adm"))
        else:
            return redirect(url_for("user", username=user["username"]))
    else:
        return redirect(url_for("login"))

@app.route("/log")
def login():
    return "Login Page"

@app.route("/users/<username>")
def user(username):
    return f"User {username}"

@app.route("/adm")
def adm():
    return "Admin Page"