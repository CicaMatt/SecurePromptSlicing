import flask
from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route("/info")
def info():
    email = request.args.get("email")
    ssn = request.args.get("ssn")
    return f"Your SSN is {ssn} and your email is {email}"