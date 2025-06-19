import hashlib
import sqlite3
from flask import Flask, request

app = Flask(__name__)

@app.route("/register", methods=['POST'])
def register():
    username = request.form.get('username')
    password = request.form.get('password')
    fname = request.form.get('fname')
    lname = request.form.get('lname')
    email = request.form.get('email')

    db = sqlite3.connect("users.db")
    c = db.cursor()

    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        return "User already exists!"

    else:
        c.execute("INSERT INTO users VALUES (?, ?)", (hashed_password, username))
        db.commit()
        return "Registration successful!"

app.run(debug=True)