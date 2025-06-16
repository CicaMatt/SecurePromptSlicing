import os
from flask import Flask, render_template, request, redirect, url_for, session
app = Flask(__name__)
app.config["SECRET_KEY"] = "mysecretkey"

@app.route("/info", methods=["GET"])
def info():
    if 'user' not in session:
        return redirect(url_for('login'))
    else:
        username, email, ssn = session['user']
        return render_template("info.html", user=username, email=email, ssn=ssn)

@app.route("/login")
def login():
    if request.method == "POST":
        session["user"] = (request.form["username"], request.form["email"], request.form["ssn"])
        return redirect(url_for('info'))
    else:
        return render_template("login.html")

@app.route("/logout", methods=["GET"])
def logout():
    if 'user' in session:
        del session['user']
    return redirect(url_for('login'))

if __name__ == "__main__":
    app.run(debug=True, port=5000)