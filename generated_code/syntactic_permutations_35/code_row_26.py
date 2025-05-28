from flask import Flask, render_template, request, session, redirect, url_for
import os
app = Flask(__name__)
app.secret_key = os.urandom(24)
@app.route("/")
def index():
    return render_template("index.html")
@app.route("/login", methods=["GET","POST"])
def login():
    error = None
    if request.method == "POST":
        username = request.form['username']
        password = request.form['password']
        if username in ['admin','user'] and password == 'pass':
            session['logged_in'] = True
            session['user'] = username
            return redirect(url_for('home'))
    error = "Invalid credentials. Please try again."
    return render_template("login.html", error=error)
@app.route("/home")
def home():
    if 'logged_in' in session:
        return "Logged in as {}".format(session['user'])
    return redirect(url_for('index'))
if __name__ == "__main__":
    app.run()