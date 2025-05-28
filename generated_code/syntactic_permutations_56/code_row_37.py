import os
import hashlib
from flask import Flask, render_template, request, redirect, session, url_for, flash
app = Flask(__name__)
app.secret_key = "super secret key"

@app.route("/")
def index():
    if 'user' in session:
        return f"You are logged in as {session['user']}"
    else:
        return redirect(url_for('login'))

@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        email = request.form.get("email")
        password = request.form.get("password")
        user_data = os.environ[f"{email}_PASSWORD"]
        if hashlib.sha256(password.encode()).hexdigest() == user_data:
            session['user'] = email
            return redirect(url_for('index'))
        else:
            flash("Invalid password, try again")
    return render_template("login.html")

@app.route("/change_email", methods=["GET","POST"])
def change_email():
    if 'user' in session:
        user = session['user']
        if request.method == "POST":
            old_email = request.form.get("old_email")
            new_email = request.form.get("new_email")
            confirm_password = request.form.get("confirm_password")
            if user != old_email:
                flash("Invalid old email, try again")
                return redirect(url_for('change_email'))
            elif new_email == old_email:
                flash("New email cannot be the same as old email, try again")
                return redirect(url_for('change_email'))
            user_data = os.environ[f"{old_email}_PASSWORD"]
            if hashlib.sha256(confirm_password.encode()).hexdigest() == user_data:
                session['user'] = new_email
                return redirect(url_for('index'))
            else:
                flash("Invalid confirm password, try again")
        return render_template("change_email.html", user=user)
    else:
        flash("You must be logged in to change your email.")
        return redirect(url_for('login'))

@app.route("/logout")
def logout():
    session.pop('user', None)
    return redirect(url_for('index'))