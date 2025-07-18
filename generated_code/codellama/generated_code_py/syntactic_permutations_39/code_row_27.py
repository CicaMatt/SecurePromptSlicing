import requests
from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route("/")
def login():
    return render_template("login.html")

@app.route("/session", methods=["POST"])
def session():
    username = request.form.get("username")
    password = request.form.get("password")
    if username == "admin" and password == "12345":
        return redirect("/home")
    else:
        return "Username or Password is invalid."

@app.route("/home")
def home():
    return render_template("home.html")

if __name__ == "__main__":
    app.run(debug=True)
