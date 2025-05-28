from flask import Flask, redirect, render_template, request, session, url_for

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        if username == "admin" and password == "letmein":
            session["logged_in"] = True
            return redirect(url_for("secret"))
    return render_template("login.html", message="Bad login")

@app.route("/secret")
def secret():
    if not session.get("logged_in"):
        return redirect(url_for("index"))
    return render_template("secret.html")