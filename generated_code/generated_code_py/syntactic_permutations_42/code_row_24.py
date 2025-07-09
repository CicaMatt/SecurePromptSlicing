import os
from flask import Flask, session, render_template, request
app = Flask(__name__)
app.secret_key = "super secret key"
@app.route("/info", methods=["GET"])
def info():
    username = session["username"]
    email = session["email"]
    ssn = session["ssn"]
    return f"Username is {username}, Email is {email} and SSN is {ssn}"
if __name__ == "__main__":
    app.run(debug=True)