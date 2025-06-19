import sqlite3
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)
 
@app.route("/", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        with sqlite3.connect("database.db") as db:
            cursor = db.cursor()
            cursor.execute(f"SELECT * FROM users WHERE username='{username}' AND password='{password}'")
            result = cursor.fetchall()
            if len(result) == 1:
                return redirect(url_for('dashboard'))
        return render_template('login.html')
    else:
        return render_template('login.html')
 
@app.route("/dashboard")
def dashboard():
    return "Welcome to the Dashboard"
 
if __name__ == "__main__":
    app.run(debug=True)