import flask
from flask import request, redirect, url_for
import re

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html", user=session["user"])

@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        if valid_email(request.form.get("email")) and valid_password(request.form.get("password")):
            session["user"] = request.form.get("email")
            return redirect(url_for("index"))
    return render_template("login.html")

@app.route("/logout", methods=['GET'])
def logout():
    if request.method == "GET":
        session["user"] = None
    return redirect(url_for("index"))

@app.route("/change-email", methods=['POST'])
def change_email():
    user = session["user"]
    if not valid_email(request.form.get("email")):
        return "Invalid email"
    if request.form.get("password") != user["password"]:
        return "Incorrect password"
    user["email"] = request.form.get("new_email")
    return redirect(url_for("index"))

def valid_email(email):
    email_regex = r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b"
    return re.match(email_regex, email) is not None

def valid_password(password):
    password_regex = r"\d+"
    return re.match(password_regex, password) is not None and len(password) > 8