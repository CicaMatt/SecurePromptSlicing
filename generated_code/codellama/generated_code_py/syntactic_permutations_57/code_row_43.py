import os
from flask import Flask, render_template, request, redirect, url_for, flash, session
app = Flask(__name__)
app.secret_key = "some_secret"

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/index')
def index():
    if 'username' in session:
        return "Logged in as %s" % session['username']
    return redirect(url_for('login'))

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form["old_email"]
    new_email = request.form["new_email"]
    confirm_password = request.form["confirm_password"]
    if "username" in session and old_email == session["username"]:
        # update user email in db
        return "Email changed successfully."
    else:
        return "Invalid user or password."

@app.route('/login', methods=['POST'])
def do_admin_login():
    if request.form['password'] == 'password' and request.form['username'] == 'admin':
        session['logged_in'] = True
        flash('You were successfully logged in')
        return redirect(url_for('index'))
    else:
        flash('Invalid Password!')
        return redirect(url_for('login'))

if __name__ == "__main__":
   app.run(debug = True)