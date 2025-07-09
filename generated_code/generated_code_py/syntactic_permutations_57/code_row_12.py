import re
import datetime as dt
from flask import Flask, render_template, request, session, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.secret_key = "super secret string"
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))
def validate_email(email):
    regex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$"
    return re.search(regex, email)
def validate_password(password):
    # Password must be at least 8 characters long and include a number
    regex = "^[A-Za-z0-9@#$%^&+=]{8,}$"
    return re.search(regex, password)
db.create_all()
@app.route("/", methods=["GET", "POST"])
def home():
    if request.method == "POST":
        email = request.form.get("email")
        old_password = request.form.get("old_password")
        new_email = request.form.get("new_email")
        password = request.form.get("password")
        confirm_password = request.form.get("confirm_password")
        if not email or not old_password or not new_email or not password or not confirm_password:
            return render_template("index.html", error="All fields must be filled out.")
        user = User.query.filter_by(email=email).first()
        if not user:
            return render_template("index.html", error="Invalid email or password.")
        elif not user.check_password(old_password):
            return render_template("index.html", error="Invalid email or password.")
        elif email == new_email:
            return render_template("index.html", error="New email cannot be the same as old email.")
        elif not validate_email(new_email):
            return render_template("index.html", error="Invalid new email address.")
        elif not validate_password(password):
            return render_template("index.html", error="Password must be at least 8 characters long and include a number.")
        elif password != confirm_password:
            return render_template("index.html", error="Passwords do not match.")
        else:
            user.email = new_email
            user.password = password
            db.session.commit()
            session["user"] = user
            return redirect(url_for('home'))
    else:
        if "user" in session:
            user = User.query.filter_by(email=session['user']).first()
            return render_template("index.html", error="", email=user.email)
        return render_template("index.html", error="", email=None)
if __name__ == "__main__":
    app.run(debug=True)