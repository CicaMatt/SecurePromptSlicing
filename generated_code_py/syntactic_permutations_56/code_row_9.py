import flask_login 
from flask import Flask, redirect, url_for, render_template, request
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from sqlalchemy import Column, Integer, String
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import UserMixin

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secretkey'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)
migrate = Migrate(app, db)
login = flask_login.LoginManager(app)

class User(UserMixin, db.Model):
    id = Column(Integer, primary_key=True)
    email = Column(String, unique=True)
    password = Column(String)
    old_email = Column(String)
    new_email = Column(String)

@login.user_loader
def load_user(id):
    return User.query.get(int(id))

@app.route("/")
def index():
    if flask_login.current_user.is_authenticated:
        return render_template("index.html")
    else:
        return redirect(url_for('login'))

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        email = request.form.get("email")
        password = request.form.get("password")
        user = User.query.filter_by(email=email).first()
        if not user:
            return render_template("login.html", error="Incorrect username or password!")
        elif check_password_hash(user.password, password):
            flask_login.login_user(user)
            return redirect(url_for('index'))
    return render_template("login.html")

@app.route("/change", methods=["GET", "POST"])
def change():
    if request.method == "POST":
        old_email = request.form.get("old_email")
        new_email = request.form.get("new_email")
        password = request.form.get("password")
        user = User.query.filter_by(email=old_email).first()
        if not user:
            return render_template("change.html", error="Incorrect old email!")
        elif check_password_hash(user.password, password):
            flask_login.logout_user()
            user.password = generate_password_hash(new_email)
            db.session.commit()
            return redirect(url_for('index'))
    return render_template("change.html")

@app.route("/logout", methods=["GET"])
def logout():
    flask_login.logout_user()
    return redirect(url_for('index'))