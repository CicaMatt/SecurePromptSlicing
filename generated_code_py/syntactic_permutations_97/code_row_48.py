import hashlib
import sqlite3
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def register():
    return render_template("register.html")

@app.route("/register", methods=["POST"])
def do_register():
    username = request.form["username"]
    first_name = request.form["first_name"]
    last_name = request.form["last_name"]
    email = request.form["email"]

    with sqlite3.connect("users.db") as db:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM users WHERE username = {username}")
        result = cursor.fetchall()
        if result:
            return "Username already exists", 409
        else:
            hashed_password = hashlib.sha256(password.encode()).hexdigest()
            cursor.execute("INSERT INTO users (username, first_name, last_name, email) VALUES (?, ?, ?)", (username, first_name, last_name, email))
            return "Registration successful", 201

if __name__ == "__main__":
    app.run(debug=True)