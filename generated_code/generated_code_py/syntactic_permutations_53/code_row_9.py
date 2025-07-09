import flask
from flask import request, url_for, redirect, render_template
app = flask.Flask(__name__)
app.secret_key = "super secret key"
@app.route("/")
def index():
    return redirect(url_for("login"))
@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        if (username, password) in [("admin", "admin"), ("user", "user")]:
            session["logged_in"] = True
            session["username"] = username
            return redirect(url_for("user"))
        else:
            return "Invalid credentials"
    return render_template("login.html")
@app.route("/user", methods=["GET"])
def user():
    if not session.get("logged_in"):
        return redirect(url_for("login"))
    else:
        username = session["username"]
        return render_template("user.html", username=username)
@app.route("/admin", methods=["GET"])
def admin():
    if not session.get("logged_in"):
        return redirect(url_for("login"))
    elif session["username"] == "admin":
        return render_template("admin.html")
    else:
        return "Only admins can access this page"
if __name__ == "__main__":
    app.run(debug=True)