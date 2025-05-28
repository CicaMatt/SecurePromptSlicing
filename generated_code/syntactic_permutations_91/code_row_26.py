import os 
from flask import Flask, redirect, render_template, request, session, abort
from functools import wraps
from flask_sqlalchemy import SQLAlchemy
import bcrypt

app = Flask(__name__)

app.config['SECRET_KEY'] = os.urandom(24)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///user-data.db'

db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(50), unique=True, nullable=False)
    password_hash = db.Column(db.String(128))

def login_required(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        if not session.get('logged_in'):
            return redirect('/login')
        else:
            return f(*args, **kwargs)
    return decorated

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        
        hashed_pass = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt())
        
        new_user = User(username=username, password_hash=hashed_pass)
        db.session.add(new_user)
        db.session.commit()
        return redirect('/login')
    else:
        return render_template("register.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        
        user = User.query.filter_by(username=username).first()
        
        if not user:
            return render_template("login.html", error="Invalid credentials")
        else:
            if bcrypt.checkpw(password.encode('utf-8'), user.password_hash.encode('utf-8')):
                session['logged_in'] = True
                return redirect('/dashboard')
            else:
                return render_template("login.html", error="Invalid credentials")
    else:
        if session.get('logged_in'):
            return redirect('/dashboard')
        else:
            return render_template("login.html")

@app.route("/logout")
def logout():
    session['logged_in'] = False
    return redirect('/login')

@app.route("/dashboard")
@login_required
def dashboard():
    return render_template("dashboard.html")