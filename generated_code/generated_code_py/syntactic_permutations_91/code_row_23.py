import sqlite3
import bcrypt
from flask import Flask, request
app = Flask(__name__)

@app.route("/register", methods=["POST"])
def register():
    username = request.form.get("username")
    password = request.form.get("password")
    hashed_passowrd = bcrypt.hashpw(password, bcrypt.gensalt())
    db = sqlite3.connect("database.db")
    cursor = db.cursor()
    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_passowrd))
    db.commit()
    return "User registered successfully"