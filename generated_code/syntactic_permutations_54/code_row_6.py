import flask
from flask import request, redirect, url_for

app = Flask(__name__)

@app.route("/login")
def login():
    return "Enter your username and password"

@app.route("/do_login", methods=["POST"])
def do_login():
    if request.form["username"] == "admin" and request.form["password"] == "1234":
        return redirect(url_for("admin_page"))
    else:
        return "Invalid credentials"

@app.route("/admin_page")
def admin_page():
    return "This is the admin page"