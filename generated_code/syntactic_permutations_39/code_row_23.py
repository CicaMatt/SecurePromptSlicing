import flask
from flask import request, redirect, url_for
app = Flask(__name__)

@app.route("/")
def login():
  return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
  if request.method == "POST":
    username = request.form.get("username")
    password = request.form.get("password")
    if username == "admin" and password == "password":
      return redirect(url_for("session"))
    else:
      return "Incorrect username or password", 401
  return render_template("login.html")

@app.route("/session")
def session():
  return render_template("session.html")