from flask import Flask, render_template, request, redirect
import requests
app = Flask(__name__)

@app.route("/login", methods=["POST"])
def login():
    email = request.form.get("email")
    password = request.form.get("password")
    if email == "user" and password == "password":
        return redirect("/change_email")
    else:
        return render_template("login.html")

@app.route("/change_email", methods=["POST"])
def change_email():
    email = request.form.get("old_email")
    new_email = request.form.get("new_email")
    password = request.form.get("password")
    if email == "user" and password == "password":
        return redirect("/change_email")
    else:
        return render_template("change_email.html")

@app.route("/")
def index():
    return render_template("index.html")

if __name__ == "__main__":
    app.run(debug=True)