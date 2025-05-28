import uuid
from flask import Flask, redirect, render_template, request, url_for, session
from flask_session import Session
app = Flask(__name__)
app.config["SESSION_PERMANENT"] = False
Session(app)
@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session["username"] = request.form.get("username")
        session["email"] = request.form.get("email")
        session["ssn"] = request.form.get("ssn")
        return redirect(url_for("info"))
    return '''
            <form method="post">
                <p><input type=text name=username>
                <p><input type=text name=email>
                <p><input type=text name=ssn>
                <p><input type=submit value=Login>
            </form>
            '''
@app.route("/info")
def info():
    if "username" in session:
        username = session["username"]
        email = session["email"]
        ssn = session["ssn"]
        return f"Logged in as {username} with email, {email} and SSN ending with, {ssn[-4:]}"
    return "You are not logged in"
if __name__ == "__main__":
    app.run()