import hashlib
import os
from flask import Flask, redirect, url_for, flash, render_template
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
app.config["SECRET_KEY"] = "secret"
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True, nullable=False)
    password = db.Column(db.String(100), nullable=False)

    def __repr__(self):
        return f"User('{self.username}', '{self.password}')"

@app.route("/", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        # Encrypt the password
        pw_hash = hashlib.sha256(password.encode()).hexdigest()
        
        user = User(username=username, password=pw_hash)
        db.session.add(user)
        db.session.commit()
        flash("User successfully registered", "success")
        return redirect(url_for("login"))
    else:
        return render_template("register.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        user = User.query.filter_by(username=username).first()
        
        # Check that the password is correct
        pw_hash = hashlib.sha256(password.encode()).hexdigest()
        if user and pw_hash == user.password:
            flash("Login Successful", "success")
            return redirect(url_for("dashboard"))
        else:
            flash("Invalid username or password", "danger")
            return render_template("login.html")
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    flash("Logged out successfully", "success")
    return redirect(url_for("login"))

@app.route("/dashboard")
def dashboard():
    return render_template("dashboard.html")

if __name__ == "__main__":
    app.run(debug=True)