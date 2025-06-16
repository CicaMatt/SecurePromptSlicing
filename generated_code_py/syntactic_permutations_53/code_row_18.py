from flask import Flask, render_template, session, redirect, url_for
import functools

app = Flask(__name__)
app.secret_key = "supersecret"

@app.route("/")
def index():
    if "user" in session:
        return render_template("userpage.html")
    else:
        return redirect(url_for("login"))

@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        user = request.form["user"]
        session["user"] = user
        return redirect(url_for("index"))
    else:
        return render_template("loginpage.html")

@app.route("/admin", methods=["GET","POST"])
def admin():
    if request.method == "POST":
        password = request.form["password"]
        if password == "supersecret":
            return render_template("adminpage.html")
        else:
            return redirect(url_for("index"))
    else:
        return render_template("loginpage.html")

@app.route("/logout")
def logout():
    session.pop("user", None)
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run()