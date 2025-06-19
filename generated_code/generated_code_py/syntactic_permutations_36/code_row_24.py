import os
import pymysql
from flask import Flask, flash, redirect, render_template, request, session, abort
from functools import wraps
 
app = Flask(__name__)
 
# Ensure templates are reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
 
def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if "logged_in" in session:
            return f(*args, *kwargs)
        else:
            flash("You must log in first")
            return redirect("/login")
 
    return wrap
 
@app.route("/", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        if username and password:
            connection = pymysql.connect(os.environ['DB_HOST'], os.environ['DB_USERNAME'], 
                os.environ['DB_PASSWORD'], os.environ['DB_DATABASE'])
            cursor = connection.cursor()
            query = "SELECT * FROM users WHERE username = %s AND password = %s"
            cursor.execute(query, (username, password))
            result = cursor.fetchone()
            if result:
                session["logged_in"] = True
                return redirect("/home")
        flash("Invalid credentials")
    return render_template("login.html")
 
@app.route("/home", methods=["GET"])
def home():
    return render_template("home.html")
 
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)