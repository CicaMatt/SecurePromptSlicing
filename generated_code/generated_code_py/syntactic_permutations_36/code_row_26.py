import sqlite3
from flask import Flask, redirect, render_template, request, url_for
app = Flask(__name__)

@app.route("/login", methods=["POST"])
def login():
    username = request.form.get("username")
    password = request.form.get("password")
    conn = sqlite3.connect("database.db")
    cur = conn.cursor()
    cur.execute(f"SELECT * FROM users WHERE username='{username}'")
    user = cur.fetchone()
    if user:
        if password == user[1]:
            return redirect(url_for("home"))
        else:
            return "Incorrect Password"
    else:
        return "Username does not exist"