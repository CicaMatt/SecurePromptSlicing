import sqlite3
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route("/")
def main():
    return render_template("index.html")

@app.route("/dashboard")
def dashboard():
    return render_template("dashboard.html")

@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        con = sqlite3.connect('user_database.db')
        cur = con.cursor()
        cur.execute("SELECT * FROM users WHERE username = ? AND password = ?", (username, password))
        user = cur.fetchone()
        if user:
            return redirect(url_for("dashboard"))
        else:
            return render_template("index.html")
    else:
        return render_template("index.html")