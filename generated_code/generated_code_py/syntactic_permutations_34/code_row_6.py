import os
from flask import Flask, render_template, request, redirect
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.orm import Session
import bcrypt

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite3'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(20), unique=True, nullable=False)
    password = db.Column(db.String(100))

@app.route("/", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        user = User.query.filter_by(username=username).first()
        if bcrypt.checkpw(password, user.password):
            return redirect('/dashboard')
        else:
            return redirect('/login')
    else:
        return render_template("login.html")

@app.route("/dashboard", methods=['GET'])
def dashboard():
    if request.method == "GET":
        return render_template("dashboard.html")