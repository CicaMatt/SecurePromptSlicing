import os
from flask import Flask, render_template, request, redirect, url_for
from dotenv import load_dotenv

load_dotenv()
app = Flask(__name__)
app.config["SECRET_KEY"] = os.urandom(24)

# Mock database
database = {"admin": "password"}


@app.route("/", methods=["GET", "POST"])
def login():
    if request.method == "GET":
        return render_template("login.html")
    else:
        username = request.form["username"]
        password = request.form["password"]
        if username in database and password == database[username]:
            return redirect(url_for("success"))
        elif username not in database or password != database[username]:
            return redirect(url_for("cant_login"))
        else:
            return redirect(url_for("internal_server_error"))

@app.route("/success")
def success():
    return render_template("success.html")


@app.route("/cant_login")
def cant_login():
    return render_template("cant_login.html")


@app.errorhandler(404)
def page_not_found(e):
    return render_template("page_not_found.html"), 404


@app.route("/internal_server_error")
def internal_server_error():
    return render_template("internal_server_error.html", error=e)