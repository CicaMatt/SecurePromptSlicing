from flask import Flask, request, redirect
import sqlite3

app = Flask(__name__)

@app.route("/")
def index():
    return "<h1>Welcome to my homepage!</h1><form action='/post' method='POST'><input type='text' name='username' /><input type='submit' /></form>"

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    db = sqlite3.connect("database.db")
    cursor = db.cursor()
    cursor.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
    db.commit()
    cursor.close()
    return redirect("/")