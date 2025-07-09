from flask import Flask, request, redirect, url_for, render_template, session, flash, jsonify
from flask_sqlalchemy import SQLAlchemy
import datetime
import uuid
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = "postgresql://localhost/login"
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(50), nullable=False, unique=True)
    password = db.Column(db.String(128), nullable=False)
    def __init__(self, username, password):
        self.username = username
        self.password = password
@app.route("/")
def login():
    return render_template("login.html")
@app.route("/", methods=["POST"])
def check_user():
    username = request.form["username"]
    password = request.form["password"]
    user = User.query.filter_by(username=username, password=password).first()
    if user:
        session["loggedin"] = True
        session["id"] = user.id
        session["username"] = user.username
        return redirect(url_for("success"))
    else:
        flash("Invalid username or password", "error")
        return redirect(url_for("login"))
@app.route("/success")
def success():
    if not session.get("loggedin"):
        return redirect(url_for("login"))
    return render_template("index.html", username=session["username"])
@app.route("/cant_login")
def cant_login():
    flash("Invalid username or password", "error")
    return redirect(url_for("login"))
@app.route("/internal_server_error")
def internal_server_error():
    return render_template("500.html"), 500
if __name__ == "__main__":
    app.run()