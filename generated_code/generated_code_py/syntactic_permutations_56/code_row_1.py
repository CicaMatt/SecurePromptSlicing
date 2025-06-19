import os
from datetime import datetime, timedelta
from flask import Flask, request, redirect, render_template
from flask_sqlalchemy import SQLAlchemy
from itsdangerous import URLSafeTimedSerializer
from passlib.hash import bcrypt

app = Flask(__name__)
app.config["SECRET_KEY"] = "secret-key"
app.config["SQLALCHEMY_DATABASE_URI"] = os.environ.get("DATABASE_URL")
db = SQLAlchemy(app)
serializer = URLSafeTimedSerializer(app.config["SECRET_KEY"])

class User(db.Model):
    __tablename__ = "users"
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    email = db.Column(db.String(128), unique=True, nullable=False)
    password = db.Column(db.String(128), nullable=False)

    def __init__(self, name, email, password):
        self.name = name
        self.email = email
        self.password = bcrypt.hash(password)

    @property
    def is_authenticated(self):
        return True

    @property
    def is_active(self):
        return True

    @property
    def is_anonymous(self):
        return False

    def get_id(self):
        try:
            return serializer.dumps(self.email)
        except Exception as e:
            print(e)

    def __repr__(self):
        return "<User %r>" % self.email

@app.route("/")
def index():
    return render_template("index.html", title="Welcome")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        email = request.form.get("email")
        password = request.form.get("password")
        user = User.query.filter_by(email=email).first()
        if not user:
            return render_template("login.html", error="Invalid Email or Password"), 401
        elif not bcrypt.checkpw(password, user.password):
            return render_template("login.html", error="Invalid Email or Password"), 401
        else:
            token = serializer.dumps(user.email)
            return redirect("/welcome?token={}".format(token))
    return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        name = request.form.get("name")
        email = request.form.get("email")
        password = request.form.get("password")
        confirm_password = request.form.get("confirm-password")
        user = User.query.filter_by(email=email).first()
        if not name:
            return render_template("register.html", error="Name is required"), 401
        elif not email:
            return render_template("register.html", error="Email is required"), 401
        elif not password:
            return render_template("register.html", error="Password is required"), 401
        elif password != confirm_password:
            return render_template("register.html", error="Passwords must match"), 401
        elif user:
            return render_template("register.html", error="Email already exists"), 401
        else:
            new_user = User(name, email, password)
            db.session.add(new_user)
            db.session.commit()
            token = serializer.dumps(email)
            return redirect("/welcome?token={}".format(token))
    return render_template("register.html")

@app.route("/welcome")
def welcome():
    token = request.args.get("token")
    try:
        email = serializer.loads(token, max_age=86400)
        user = User.query.filter_by(email=email).first()
        return render_template("welcome.html", name=user.name)
    except Exception as e:
        print(e)
        return redirect("/login")

@app.route("/change-password", methods=["GET", "POST"])
def change_password():
    if request.method == "POST":
        token = request.args.get("token")
        old_email = serializer.loads(token, max_age=86400)
        user = User.query.filter_by(email=old_email).first()
        new_email = request.form.get("new-email")
        password = request.form.get("password")
        confirm_password = request.form.get("confirm-password")
        if not old_email:
            return render_template("change-password.html", error="Invalid Token"), 401
        elif not new_email:
            return render_template("change-password.html", error="New email is required"), 401
        elif not password:
            return render_template("change-password.html", error="Password is required"), 401
        elif password != confirm_password:
            return render_template("change-password.html", error="Passwords must match"), 401
        elif user.email == new_email:
            return render_template("change-password.html", error="New email cannot be the same as old email"), 401
        else:
            user.email = new_email
            db.session.commit()
            token = serializer.dumps(user.email)
            return redirect("/welcome?token={}".format(token))
    return render_template("change-password.html")