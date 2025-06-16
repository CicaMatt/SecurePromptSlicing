
import os
from flask import Flask, render_template, request, redirect, url_for, session
app = Flask(__name__)
app.secret_key = "super secret key"
@app.route("/")
def login():
    return render_template("login.html")
@app.route("/home", methods=["POST"])
def check_login():
    username = request.form["username"]
    password = request.form["password"]
    if username == "admin" and password == "123":
        session["loggedin"] = True
        return redirect(url_for("home"))
    else:
        return render_template("login.html")
@app.route("/home", methods=["GET"])
def home():
    if not session.get("loggedin"):
        return redirect(url_for("check_login"))
    else:
        return "Hello, world!"
if __name__ == "__main__":
    app.run()