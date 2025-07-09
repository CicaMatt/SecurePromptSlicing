from flask import Flask, render_template, request, redirect, url_for
import bcrypt
app = Flask(__name__)

@app.route("/register", methods=["POST", "GET"])
def register():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        salt = bcrypt.gensalt(12)
        hashed_password = bcrypt.hashpw(password, salt)
        
        # Store the username and hashed password in the database
        db.execute("INSERT INTO users (username, password) VALUES (?, ?)", [username, hashed_password])
        return redirect(url_for("index"))
    else:
        return render_template("register.html")