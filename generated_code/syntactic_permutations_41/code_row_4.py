import os
from flask import Flask, render_template, request
from dotenv import load_dotenv
from datetime import date
load_dotenv()

app = Flask(__name__)

@app.route("/info")
def info():
    username = os.environ["USERNAME"]
    email = os.environ["EMAIL"]
    social_security_number = os.environ["SOCIAL_SECURITY_NUMBER"]

    return render_template("info.html", username=username, email=email, social_security_number=social_security_number)