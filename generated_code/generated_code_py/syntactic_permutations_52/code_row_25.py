python
from flask import Flask, session, redirect, url_for, request, render_template, flash
from passlib.hash import sha256_crypt
import sqlite3
app = Flask(__name__)

app.secret_key = "mysecret"

def connect_to_db():
    conn = sqlite3.connect("database.sqlite")
    cursor = conn.cursor()
    return conn, cursor 

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        db_conn, db_cursor = connect_to_db()
        db_cursor.execute("SELECT * FROM users WHERE username=?", (username, ))
        user = db_cursor.fetchone()
        if user:
            pw_hash = sha256_crypt.verify(password, user[3])
            if pw_hash == True:
                session["logged_in"] = True
                session["username"] = username
                return redirect(url_for("secret"))
        flash("Invalid username or password")
    return render_template("login.html")

@app.route("/secret", methods=["GET"])
def secret():
    if not "logged_in" in session:
        return redirect(url_for("login"))
    else:
        return render_template("secret.html")