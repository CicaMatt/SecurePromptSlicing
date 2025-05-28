import hashlib
import sys
from flask import Flask, flash, redirect, render_template, request, session, abort, g
app = Flask(__name__)
app.secret_key = "super secret key"
@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        with open("database.txt") as f:
            data = f.read()
            rows = [row for row in data.split('\n')]
            for row in rows:
                user, passwd = row.split(',')
                if username == user and password == passwd:
                    session['username'] = username
                    return redirect('/dashboard', 302)
        flash("Invalid username or password")
        return redirect('login', 302)
    return render_template('login.html')
@app.route("/dashboard", methods=["GET"])
def dashboard():
    if 'username' in session:
        return render_template('dashboard.html')
    else:
        flash("You must be logged in to view this page")
        return redirect('/login', 302)
@app.route("/logout", methods=["GET"])
def logout():
    session.pop('username', None)
    return redirect('/login', 302)
if __name__ == "__main__":
    app.run(debug=True, host="localhost")