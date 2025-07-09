import os
from flask import Flask, render_template, request, session, url_for
app = Flask(__name__)
app.config["SECRET_KEY"] = "1234567890"
@app.route("/")
def home():
    return render_template("login.html")

@app.route("/check", methods=["POST"])
def check():
    username = request.form["username"]
    password = request.form["password"]
    if username == "admin" and password == "1234":
        session["user"] = username
        return redirect(url_for("dashboard"))
    else:
        return render_template("login.html", message="Invalid Credentials")

@app.route("/dashboard")
def dashboard():
    if "user" in session:
        username = session["user"]
        return f"Welcome {username}"
    else:
        return redirect(url_for("login"))
if __name__ == "__main__":
    app.run(debug=True)