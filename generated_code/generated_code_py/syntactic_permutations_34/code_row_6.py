import sqlite3
from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = "super secret key"

@app.route("/")
def index():
    return render_template("login.html")


@app.route("/login", methods=["POST"])
def login():
    username = request.form["username"]
    password = request.form["password"]
    db = sqlite3.connect("users.db")
    cursor = db.cursor()
    cursor.execute(
        "SELECT * FROM users WHERE username=(?) AND password=(?)",
        (username, password),
    )
    result = cursor.fetchone()
    if result:
        flash("Logged in successfully!")
        return redirect(url_for("dashboard"))
    else:
        flash("Invalid credentials!")
        return redirect(url_for("index"))


@app.route("/dashboard")
def dashboard():
    return "You are logged in!"


if __name__ == "__main__":
    app.run()