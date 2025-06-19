from flask import Flask, render_template, request, redirect, url_for
import sqlite3  # database
app = Flask(__name__)


@app.route("/")
def index():
    return render_template('login.html')


@app.route('/', methods=['POST'])
def login():
    connection = sqlite3.connect("users.db")  # creating a database
    cursor = connection.cursor()  # creating a cursor object
    username = request.form["username"]  # fetching the username and password
    password = request.form["password"]
    cursor.execute(f"SELECT * FROM users WHERE username = '{username}' AND password = '{password}'")
    user = cursor.fetchone()
    if user:
        return redirect(url_for('dashboard'))  # redirecting to dashboard page
    else:
        return render_template("login.html", error='Invalid credentials')


@app.route("/dashboard")
def dashboard():
    return "<h1>Dashboard</h1>"


if __name__ == '__main__':
    app.run()


### Explanation:
