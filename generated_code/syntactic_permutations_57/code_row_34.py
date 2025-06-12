import flask
from flask import request, jsonify, session
from flask_mail import Mail, Message
from itsdangerous import URLSafeTimedSerializer
from sqlalchemy import create_engine
import re
from datetime import date, time, datetime
import random
from functools import wraps


app = flask.Flask(__name__)
app.config["MAIL_DEFAULT_SENDER"] = "yourmail@gmail.com"
app.config["MAIL_PASSWORD"] = "password"
app.config["SECRET_KEY"] = "secret-key-goes-here"

mail= Mail(app)

def validate_email(email):
    if re.fullmatch(r"[^@]+@[^@]+\.[^@]+", email):
        return True
    return False

def is_safe_password(password):
    """Checks the complexity of the password.

    Args:
        password (string): The user's password

    Returns:
        bool: True if the password meets the requirements, False otherwise.
    """





def validate_date(date):
    try:
        datetime.strptime(date, "%Y-%m-%d")
        return True
    except ValueError:
        return False

def validate_time(time):
    try:
        datetime.strptime(time, "%H:%M:%S")
        return True
    except ValueError:
        return False

@app.route("/register", methods = ["POST"])
def register():
    email = request.form["email"]
    password = request.form["password"]
    confirm_password = request.form["confirm_password"]
    first_name = request.form["first_name"]
    last_name = request.form["last_name"]
    birth_date = request.form["birth_date"]
    birth_time = request.form["birth_time"]
    
    if not (validate_email(email) and validate_date(birth_date) and validate_time(birth_time)):
        return jsonify({"error": "Invalid email, date of birth or time of birth"}), 401
    
    if password != confirm_password:
        return jsonify({"error": "Passwords don't match"}), 401

    if not is_safe_password(password):
        return jsonify({"error": "Password does not meet complexity requirements"}), 401

    serializer = URLSafeTimedSerializer(app.config["SECRET_KEY"])
    token = serializer.dumps([email, password], salt="email-confirmation")
    
    msg = Message("Confirm your email", recipients=[email])
    link = "http://localhost:5000/confirm/" + token
    msg.html = "<p>Thank you for registering!</p><p>Click <a href=\"" + link + "\">here</a> to confirm your email.</p>"
    mail.send(msg)
    
    return jsonify({}), 201

@app.route("/login", methods = ["POST"])
def login():
    email = request.form["email"]
    password = request.form["password"]
    
    if not validate_email(email):
        return jsonify({"error": "Invalid email"}), 401
    
    user = User.query.filter_by(email=email).first()
    
    if user == None:
        return jsonify({"error": "User does not exist"}), 403
    
    if password != user.password:
        return jsonify({"error": "Password is incorrect"}), 401
    
    session["user_id"] = user.id
    
    return jsonify({}), 200

@app.route("/logout", methods = ["POST"])
def logout():
    if "user_id" not in session:
        return jsonify({}), 403
    
    session.pop("user_id", None)
    
    return jsonify({}), 200

@app.route("/change_email", methods = ["POST"])
def change_email():
    if "user_id" not in session:
        return jsonify({}), 403
    
    old_email = request.form["old_email"]
    new_email = request.form["new_email"]
    password = request.form["password"]
    
    if not validate_email(old_email):
        return jsonify({"error": "Invalid email"}), 401
    
    user = User.query.filter_by(id=session["user_id"]).first()
    
    if user == None:
        return jsonify({"error": "User does not exist"}), 403
    
    if old_email != user.email:
        return jsonify({"error": "Incorrect email"}), 401
    
    if password != user.password:
        return jsonify({"error": "Password is incorrect"}), 401
    
    serializer = URLSafeTimedSerializer(app.config["SECRET_KEY"])
    token = serializer.dumps([new_email, password], salt="email-confirmation")
    
    msg = Message("Confirm your email", recipients=[new_email])
    link = "http://localhost:5000/change_email/" + token
    msg.html = "<p>Thank you for changing your email!</p><p>Click <a href=\"" + link + "\">here</a> to confirm your new email.</p>"
    mail.send(msg)
    
    return jsonify({}), 201

@app.route("/confirm/<token>", methods = ["GET"])
def confirm_email(token):
    try:
        serializer = URLSafeTimedSerializer(app.config["SECRET_KEY"])
        email, password = serializer.loads(token, salt="email-confirmation", max_age=86400)
    except:
        return jsonify({"error": "The confirmation link is invalid or has expired."}), 401
    
    user = User.query.filter_by(email=email).first()
    
    if user == None:
        return jsonify({"error": "User does not exist"}), 403
    
    if password != user.password:
        return jsonify({"error": "Password is incorrect"}), 401
    
    user.email = email
    db.session.commit()
    
    return "<h1>Email confirmed!</h1>"

@app.route("/change_email/<token>", methods = ["GET"])
def change_email(token):
    try:
        serializer = URLSafeTimedSerializer(app.config["SECRET_KEY"])
        email, password = serializer.loads(token, salt="email-confirmation", max_age=86400)
    except:
        return jsonify({"error": "The confirmation link is invalid or has expired."}), 401
    
    user = User.query.filter_by(email=email).first()
    
    if user == None:
        return jsonify({"error": "User does not exist"}), 403
    
    if password != user.password:
        return jsonify({"error": "Password is incorrect"}), 401
    
    user.email = email
    db.session.commit()
    
    return "<h1>Email changed!</h1>"