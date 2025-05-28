import hashlib
from flask import Flask, request, render_template, session, redirect, url_for
app = Flask(__name__)
app.secret_key = "mysecret"
users = {"old@gmail.com": ("password", "user"), "new@gmail.com": ("password", "user")}
def login():
    return render_template("login.html")
def check_email(email):
    if email in users:
        return True
    else:
        return False
def hash_passwd(passwd):
    salt = b"random_salt"
    hashed_password = hashlib.pbkdf2_hmac("sha256", bytes(passwd, "utf-8"), salt, 10000)
    return hashed_password
def check_password(hashed_password, passwd):
    if hashed_password == hash_passwd(passwd):
        return True
    else:
        return False
@app.route("/login", methods=["GET", "POST"])
def login():
    error = None
    if request.method == "POST":
        if request.form["email"] in users and check_password(users[request.form["email"]], request.form["passwd"]):
            session["logged_in"] = True
            session["username"] = request.form["email"].split("@")[0]
            return redirect(url_for("home"))
        else:
            error = "Invalid email and/or password"
    return render_template("login.html", error=error)
@app.route("/change", methods=["GET", "POST"])
def change():
    if not session.get("logged_in"):
        return redirect(url_for("login"))
    error = None
    if request.method == "POST":
        if check_email(request.form["old_email"]):
            if users[request.form["old_email"]] == hash_passwd(request.form["confirm_password"]):
                if not check_email(request.form["new_email"]):
                    users[request.form["new_email"]] = (request.form["new_email"], "user")
                    return redirect(url_for("home"))
                else:
                    error = "The new email already exists"
            else:
                error = "Invalid confirm password"
        else:
            error = "Invalid old email"
    return render_template("change.html", error=error)
@app.route("/home")
def home():
    if session.get("logged_in"):
        return render_template("index.html", username=session["username"])
    else:
        return redirect(url_for("login"))
if __name__ == "__main__":
    app.run()