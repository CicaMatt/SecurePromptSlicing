import os
from flask import Flask, request, session, redirect, url_for
from passlib.hash import sha256_crypt
import MySQLdb

app = Flask(__name__)

@app.route("/")
def index():
    return "Hello, World!"

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form["username"]
        password = sha256_crypt.encrypt(str(request.form["password"]))

        db = MySQLdb.connect("localhost", "root", "", "myflaskapp")
        cursor = db.cursor()
        cursor.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, password))

        return "You are now registered!"
    else:
        return "Hello, World!"

if __name__ == "__main__":
    app.run(debug=True)