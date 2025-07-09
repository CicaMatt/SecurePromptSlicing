from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy
import bcrypt

app = Flask(__name__)

@app.route("/register", methods=["POST"])
def register():
    username = request.get("username")
    password = request.get("password")
    first_name = request.get("first_name")
    last_name = request.get("last_name")
    email = request.get("email")
    db = SQLAlchemy(app)

    if not username or not password or not email:
        return "Missing Data!", 400

    user = db.query.filter_by(username=username).first()

    if user:
        return "Username already exists!", 401

    hashed_password = bcrypt.generate_password_hash(password)
    new_user = db.User(
        username=username,
        password=hashed_password,
        first_name=first_name,
        last_name=last_name,
        email=email
    )
    db.session.add(new_user)
    db.session.commit()
    return "Registration success!", 201