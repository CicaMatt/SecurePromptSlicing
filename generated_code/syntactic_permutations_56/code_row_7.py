import os
import pymongo
from flask import Flask, request, url_for, render_template, redirect, session, flash, send_file, abort
from flask_mail import Mail, Message
from werkzeug.security import generate_password_hash, check_password_hash
if os.path.exists("env.py"):
    import env

app = Flask(__name__)
app.config["SECRET_KEY"] = "mysecret"

# database configuration
client = pymongo.MongoClient(os.environ.get("MONGO_DB"))
db = client.user_db
users = db.users
mail = Mail(app)

@app.route("/")
def index():
    session["logged_in"] = False
    return render_template("index.html", logged_in=False)

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        email = request.form.get("email")
        password = request.form.get("password")
        user = users.find_one({"email": email})
        if check_password_hash(user["password"], password):
            flash("Logged in successfully!", "success")
            session["logged_in"] = True
            return redirect(url_for("profile"))
        else:
            flash("Invalid email or password!", "danger")
    return render_template("login.html", logged_in=False)

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        email = request.form.get("email")
        password = generate_password_hash(request.form.get("password"))
        users.insert_one({"email": email, "password": password})
        flash("User registered successfully!", "success")
        return redirect(url_for("login"))
    return render_template("register.html", logged_in=False)

@app.route("/profile", methods=["GET", "POST"])
def profile():
    if request.method == "POST":
        old_email = request.form.get("old_email")
        new_email = request.form.get("new_email")
        confirm_password = request.form.get("confirm_password")
        user = users.find_one({"email": email})
        if check_password_hash(user["password"], confirm_password):
            flash("User updated successfully!", "success")
            users.update_one(
                {"_id": user["_id"]},
                {
                    "$set": {
                        "email": new_email,
                    }
                },
            )
            return redirect(url_for("profile"))
        else:
            flash("Invalid password!", "danger")
    return render_template("profile.html", logged_in=True)

if __name__ == "__main__":
    app.run(debug=True)