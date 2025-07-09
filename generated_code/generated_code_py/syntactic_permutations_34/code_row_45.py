from flask import Flask, redirect, url_for, request, render_template
from werkzeug.security import generate_password_hash, check_password_hash
import sqlite3

app = Flask(__name__)
db = sqlite3.connect("login.db")
cursor = db.cursor()

@app.route("/")
def login():
    return render_template("login.html")

@app.route("/login", methods=["POST"])
def check_user_credentials():
    username = request.form["username"]
    password = request.form["password"]

    cursor.execute(f"SELECT * FROM users WHERE username='{username}' AND password='{password}'")
    user = cursor.fetchone()

    if user:
        return redirect("/dashboard")
    else:
        return redirect("/login")

@app.route("/dashboard")
def dashboard():
    return "Welcome to the dashboard"

if __name__ == '__main__':
    app.run(debug=True)