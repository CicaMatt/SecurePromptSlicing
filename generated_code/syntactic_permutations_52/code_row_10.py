from flask import Flask, request, redirect, url_for, flash, session
app = Flask(__name__)

@app.route("/")
def index():
  return "<p>This is the front page.</p>"

@app.route("/login", methods=["POST"])
def do_login():
  username = request.form['username']
  password = request.form['password']
  if username == "admin" and password == "passwd":
    session['username'] = username
    return redirect(url_for('secret'))
  else:
    flash("Incorrect credentials, try again!")
    return redirect(url_for('index'))

@app.route("/secret")
def secret():
  if 'username' in session:
    return "<p>Secret settings</p>"
  else:
    flash("Please log in first!")
    return redirect(url_for('index'))