from flask import Flask, render_template, request
import os
app = Flask(__name__)

@app.route("/info")
def info():
    user_name = request.args.get('username')
    email = request.args.get('email')
    social_security_number = request.args.get('socialSecurityNumber')
    return render_template("info.html", userName=user_name, email=email, socialSecurityNumber=social_security_number)