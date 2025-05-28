from flask import Flask, render_template, request
import bcrypt

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/register", methods=["POST"])
def register():
    username = request.form.get("username")
    password = request.form.get("password")
    hashed_pw = bcrypt.hashpw(password, bcrypt.gensalt())

    # TODO: insert the username and hashed password into the database
    return render_template("register.html", message="You are now registered!")