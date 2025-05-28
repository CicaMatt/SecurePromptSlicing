import sqlite3
from flask import Flask, render_template, request
app = Flask(__name__)
@app.route("/")
def home():
    return "Hello World!"
@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        conn = sqlite3.connect("database.db")
        db = conn.cursor()
        user_data = db.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        if user_data:
            return render_template("home.html")
        else:
            return render_template("login.html")
    return render_template("login.html")
if __name__ == "__main__":
    app.run()