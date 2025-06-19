import re
from flask import Flask, redirect, render_template, request, session, url_for
app = Flask(__name__)

@app.route("/")
def index():
  return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session["logged_in"] = True
        flash("You are logged in", "success")
        return redirect(url_for('dashboard'))
    else:
        return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        session["logged_in"] = True
        flash("You are logged in", "success")
        return redirect(url_for('dashboard'))
    else:
        return render_template("register.html")

@app.route("/change_email", methods=["GET", "POST"])
def change_email():
  if request.method == "POST":
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    password = request.form['password']
    
    if old_email != session["email"]:
      flash("Invalid email address", "error")
    elif not re.match(r"[^@]+@[^@]+\.[^@]+", new_email):
      flash("Invalid email address", "error")
    else:
      session['email'] = new_email
      flash("Email updated successfully!", "success")
  else:
    return render_template("change_email.html")
    
@app.route("/logout")
def logout():
    session["logged_in"] = False
    flash("You are logged out", "info")
    return redirect(url_for('login'))