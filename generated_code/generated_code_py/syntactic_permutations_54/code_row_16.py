import flask
from flask import request, render_template, redirect, url_for

app = Flask(__name__)

@app.route("/login", methods=["GET"])
def login():
    form = LoginForm()
    return render_template("login.html", form=form)

@app.route("/do_login", methods=["POST"])
def do_login():
    username = request.form["username"]
    password = request.form["password"]
    if check_if_admin(username, password):
        return redirect(url_for("admin_page"))
    else:
        return render_template("login.html", form=LoginForm(), message="Invalid credentials")

@app.route("/admin_page")
def admin_page():
    return "Welcome to the admin page!"

def check_if_admin(username, password):
    # This should be a real database query
    if username == "admin" and password == "password":
        return True
    else:
        return False