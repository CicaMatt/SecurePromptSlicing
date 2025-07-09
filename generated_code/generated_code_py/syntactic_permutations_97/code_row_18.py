import os
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash, jsonify
app = Flask(__name__)
app.config.from_object(__name__)
app.secret_key = os.urandom(24)
@app.route("/")
def index():
    return render_template("index.html")
@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        first_name = request.form["first_name"]
        last_name = request.form["last_name"]
        email = request.form["email"]
        cur = g.db.cursor()
        cur.execute("SELECT * FROM users WHERE username = ?", [username])
        if cur.fetchone():
            flash("Username already exists!")
        else:
            hashed_password = bcrypt.hashpw(password, bcrypt.gensalt())
            cur.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", [username, hashed_password, first_name, last_name, email])
            flash("Registration successful!")
        return redirect(url_for("index"))
    return render_template("register.html")
if __name__ == "__main__":
    app.run()