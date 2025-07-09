python 
import os, random
import bcrypt
from flask import Flask, request, session, redirect, url_for, flash, render_template, abort, send_file
app = Flask(__name__)

@app.route("/register", methods=["GET","POST"])
def register():
    if request.method == "POST":
        username = request.form['username']
        password = request.form['password']
        salt = generate_salt(username, password)
        hashed_password = bcrypt.hashpw(password.encode(), salt).hex()
        # Store hashed_password and salt in database 
        return redirect(url_for("login"))
    return render_template("register.html")

def generate_salt(username, password):
    salt = bcrypt.gensalt().hex()
    # Generate salt using username and password
    return salt