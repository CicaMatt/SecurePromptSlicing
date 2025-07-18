import os
from flask import Flask, request, redirect, url_for, render_template

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def home():
    return "<h1>Welcome Home</h1>"

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        with open("database.txt") as file:
            data = file.read()
            if f"{username}\n{password}" in data:
                return redirect(url_for("home"))
    return render_template("login.html")

if __name__ == "__main__":
    app.run(debug=True)