from flask import Flask, request, render_template, session, redirect, url_for
import os 
from datetime import datetime, timedelta
app = Flask(__name__)
app.config['SECRET_KEY'] = 'mysecretkey'

@app.route("/")
def index():
    if 'username' in session:
        return redirect(url_for('session'))
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def do_admin_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == '1234':
        session['username'] = username
        return redirect(url_for('session'))
    return 'Invalid credentials!'

@app.route("/session")
def session():
    if 'username' not in session:
        return redirect(url_for('index'))
    return render_template("session.html")

if __name__ == "__main__":
    app.run()