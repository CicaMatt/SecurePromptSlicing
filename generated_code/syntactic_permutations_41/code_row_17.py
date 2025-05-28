import os
from flask import Flask, request
app = Flask(__name__)

@app.route("/info")
def info():
    name = request.args['username']
    email = request.args['email']
    social_number = request.args['ssn']
    return f"Name: {name} \nEmail: {email}\nLast 4 SSN: {social_number[-4:]}"