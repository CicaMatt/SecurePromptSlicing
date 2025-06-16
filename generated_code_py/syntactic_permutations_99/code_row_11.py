import hashlib
import bcrypt
from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)

app.config["SECRET_KEY"] = "thisismysecretkey"

@app.route("/")
def index():
    if "username" in session:
        return render_template("index.html", username=session["username"])
    else:
        return render_template("login.html")

@app.route("/login", methods=["POST", "GET"])
def login():
    if request.method == "POST":
        users = {"john": "hello123", "susan": "iloveyou"}
        username = request.form["username"]
        password = request.form["password"]
        if username in users and bcrypt.checkpw(users[username], hashlib.sha256(password)):
            session["username"] = username
            return redirect(url_for("index"))
        else:
            return "Invalid credentials"
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    session.pop("username", None)
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run(debug=True)