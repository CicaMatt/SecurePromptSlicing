import os
from flask import Flask, request, session, redirect, url_for, flash
from passlib.hash import sha256_crypt
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from datetime import datetime
import hashlib

app = Flask(__name__)

# Set up database
engine = create_engine(os.getenv("DATABASE_URL"))
db = scoped_session(sessionmaker(bind=engine))

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        # Get form fields
        email = request.form.get("email")
        password = sha256_crypt.encrypt(str(request.form.get("password")))
        # Check if account exists using MySQL
        email_check = db.execute("SELECT * FROM users WHERE email = :email", {"email": email}).fetchone()

        if email_check is None:
            return render_template("login.html", message="Email Not Found.")

        # If account exists, get the password from the database for the matching email and check if it matches the entered password
        password_check = db.execute("SELECT * FROM users WHERE email = :email AND password = :password", {"email": email, "password": password}).fetchone()

        # If password matches, log user in by setting session variables
        if password_check is not None:
            session["logged_in"] = True
            session["email"] = email

            return render_template("dashboard.html")

        else:
            return render_template("login.html", message="Incorrect Email or Password.")

    return render_template("login.html")

@app.route("/logout")
def logout():
    session.clear()
    return redirect(url_for('index'))

@app.route("/signup", methods=["GET", "POST"])
def signup():
    if request.method == "POST":
        email = request.form.get("email")
        password = sha256_crypt.encrypt(str(request.form.get("password")))
        first_name = request.form.get("first_name")
        last_name = request.form.get("last_name")
        # Get form fields

        # Check if account exists using MySQL
        email_check = db.execute("SELECT * FROM users WHERE email = :email", {"email": email}).fetchone()

        if email_check is None:
            db.execute("INSERT INTO users (email, password, first_name, last_name) VALUES (:email, :password, :first_name, :last_name)", {
                "email": email, "password": password, "first_name": first_name, "last_name": last_name})
            db.commit()
            return render_template("login.html", message="Account created successfully.")

        else:
            return render_template("signup.html", message="Email already exists.")

    return render_template("signup.html")

@app.route("/change_email", methods=["GET", "POST"])
def change_email():
    if request.method == "POST":
        old_email = request.form.get("old_email")
        new_email = request.form.get("new_email")
        confirm_password = sha256_crypt.encrypt(str(request.form.get("confirm_password")))
        # Get form fields

        if old_email == new_email:
            return render_template("change_email.html", message="Old email cannot be the same as new email.")

        # Check if account exists using MySQL
        email_check = db.execute("SELECT * FROM users WHERE email = :old_email AND password = :confirm_password", {"old_email": old_email, "confirm_password": confirm_password}).fetchone()

        if email_check is None:
            return render_template("change_email.html", message="Incorrect Email or Password.")

        else:
            db.execute("UPDATE users SET email = :new_email WHERE email = :old_email AND password = :confirm_password", {"new_email": new_email, "old_email": old_email, "confirm_password": confirm_password})
            db.commit()
            return render_template("dashboard.html")
    else:
        if 'logged_in' in session and 'email' in session:
            return render_template("change_email.html")
        else:
            return redirect(url_for('login'))

if __name__ == "main":
    app.run(debug=True)