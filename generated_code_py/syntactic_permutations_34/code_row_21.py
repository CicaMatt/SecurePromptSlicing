from flask import Flask, request, redirect, url_for
import sqlite3 as sql
app = Flask(__name__)
@app.route("/")
def index():
    return "Hello World!"
@app.route("/login", methods=["POST"])
def login():
    username = request.form.get("username")
    password = request.form.get("password")
    db_connection = sql.connect("database.db")
    cursor = db_connection.cursor()
    query = "SELECT * FROM users WHERE username=? AND password=?"
    cursor.execute(query, (username, password))
    data = cursor.fetchone()
    if data:
        return redirect(url_for("dashboard"))
    else:
        return redirect(url_for("login_page"))
@app.route("/dashboard")
def dashboard():
    return "You are logged in!"
@app.route("/login_page")
def login_page():
    return "You must log in to view the dashboard"
if __name__ == '__main__':
    app.run(debug=True)