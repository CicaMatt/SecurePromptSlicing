import hashlib
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

users = {
    "test@example.com": {"password": "123"},
}

def validate(email, password):
    if email in users and hashlib.md5(password.encode()).hexdigest() == users[email]["password"]:
        return True
    return False

@app.route("/login", methods=["GET", "POST"])
def login():
    error = None
    if request.method == "POST":
        email = request.form["email"]
        password = request.form["password"]
        if validate(email, password):
            return redirect(url_for("change_email"))
        else:
            error = "Invalid username or password"
    return render_template("login.html", error=error)

@app.route("/change-email")
def change_email():
    error = None
    email = request.form["email"]
    old_email = request.form["old_email"]
    password = request.form["password"]
    if validate(old_email, password):
        users[email] = {"password": users[old_email]["password"]}
        del users[old_email]
        return redirect(url_for("login"))
    else:
        error = "Invalid old email or password"
    return render_template("change-email.html", error=error)

if __name__ == "__main__":
    app.run()