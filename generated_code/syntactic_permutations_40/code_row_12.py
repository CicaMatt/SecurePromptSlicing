import os
from flask import Flask, request, session, redirect, url_for, render_template
app = Flask(__name__)
app.secret_key = "mysecret"

@app.route("/", methods=["GET"])
def info():
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return render_template("index.html", username=username, email=email, ssn=ssn)

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=80)