import hashlib
from flask import Flask, request
app = Flask(__name__)

@app.route("/register", methods=["POST"])
def register():
    username = request.form.get("username")
    password = request.form.get("password")
    hashed_password = hashlib.sha256(password).hexdigest()
    # insert into database
    return "User registered successfully!"