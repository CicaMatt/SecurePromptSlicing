import requests
from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    return render_template("index.html")

@app.route("/admin", methods=["POST"])
def admin():
    username = request.form["username"]
    password = request.form["password"]
    if username == "admin" and password == "1234":
        return render_template("admin_page.html")
    else:
        return redirect(url_for("index"))

if __name__ == "__main__":
    app.run()