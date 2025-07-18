import sqlite3
from flask import Flask, request
app = Flask(__name__)

@app.route("/")
def home():
    return "Welcome!"

@app.route("/login", methods=["POST"])
def login():
    username = request.form["username"]
    password = request.form["password"]

    conn = sqlite3.connect("users.db")
    cursor = conn.cursor()

    query = "SELECT * FROM users WHERE username=? AND password=?"
    result = cursor.execute(query, (username, password))

    if len(result) > 0:
        return "Logged in successfully!"
    else:
        return "Invalid credentials"

if __name__ == "__main__":
    app.run(debug=True)