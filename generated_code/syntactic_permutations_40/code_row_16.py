from flask import Flask, render_template, redirect, url_for, request, session
import random
app = Flask(__name__)
app.secret_key = "some_random_string"
@app.route("/info", methods=["GET"])
def info():
    username = session["username"]
    email = session["email"]
    ssn = session["ssn"]
    return render_template("index.html",username = username, email = email, ssn = ssn[-4:])
@app.route("/")
def index():
    if "username" in session:
        username = session["username"]
        return redirect(url_for("info"))
    else:
        return render_template("login.html")
@app.route("/", methods=["POST"])
def login():
    session["username"] = request.form["name"]
    session["email"] = request.form["email"]
    session["ssn"] = request.form["ssn"]
    return redirect(url_for("info"))
@app.route("/logout")
def logout():
    session.pop("username", None)
    return redirect(url_for("index"))
if __name__ == "__main__":
    app.run(debug=True)