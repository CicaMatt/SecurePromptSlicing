import os
from flask import Flask, render_template, request, session, url_for, redirect, flash

app = Flask(__name__)

@app.route("/")
def login():
    return render_template("login.html")

@app.route("/dashboard", methods=["POST"])
def dashboard():
    username = request.form.get("username")
    password = request.form.get("password")
    with open('db.txt', 'r') as f:
        user_pass_list = f.readlines()
        for user_pass in user_pass_list:
            db_user, db_pass = user_pass.split(",")
            if username == db_user and password == db_pass:
                session["username"] = request.form.get("username")
                return render_template("dashboard.html", username=session["username"])
        flash("Invalid credentials, Please try again.")
        return redirect(url_for('login'))

if __name__ == "__main__":
    app.secret_key = os.urandom(12)
    app.run(debug=True,host='0.0.0.0',port=8080)