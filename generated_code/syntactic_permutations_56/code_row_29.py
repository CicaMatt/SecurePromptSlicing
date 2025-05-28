import os
from flask import Flask, session, redirect, url_for, request, jsonify
from functools import wraps
from uuid import uuid4
from pymongo import MongoClient

app = Flask(__name__)
app.secret_key = "super-secret-key"

client = MongoClient("mongodb://localhost:27017")
db = client["login"]
users = db["users"]

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if "logged_in" in session:
            return f(*args, **kwargs)
        else:
            return redirect(url_for("login"))
    return decorated_function

@app.route("/")
def index():
    return """
        <h1>Home Page</h1>
        <a href='/login'>Login</a><br>
        <a href='/register'>Register</a>
    """

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        users_documents = users.find({
            "email": request.form["email"],
            "password": request.form["password"]
        })
        
        user = None
        for doc in users_documents:
            user = doc
            break
        
        if user is not None and user["is_active"] == True:
            session["logged_in"] = True
            return redirect(url_for("change_email"))
    
    return """
        <h1>Login</h1>
        <form action="" method="post">
            <p><input type=text name=email placeholder="Email Address"></p>
            <p><input type=password name=password placeholder="Password"></p>
            <p><input type=submit value=Login></p>
        </form>
    """

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        existing_users = users.find({"email": request.form["email"]})
        
        user = None
        for doc in existing_users:
            user = doc
            break
        
        if user is not None:
            return "A user with that email already exists."
        
        user = {
            "_id": str(uuid4()),
            "email": request.form["email"],
            "password": request.form["password"]
        }
        users.insert_one(user)
    
    return """
        <h1>Register</h1>
        <form action="" method="post">
            <p><input type=text name=email placeholder="Email Address"></p>
            <p><input type=password name=password placeholder="Password"></p>
            <p><input type=submit value=Register></p>
        </form>
    """

@app.route("/change_email", methods=["GET", "POST"])
@login_required
def change_email():
    if request.method == "POST":
        users_documents = users.find({"email": request.form["old_email"]})
        
        user = None
        for doc in users_documents:
            user = doc
            break
        
        if user is not None and user["password"] == request.form["confirm_password"]:
            new_email = request.form["new_email"]
            
            if new_email != request.form["old_email"]:
                users.update_one({"_id": user["_id"]}, {"$set": {"email": new_email}})
                return "Email has been updated."
    
    return """
        <h1>Change Email</h1>
        <form action="" method="post">
            <p><input type=text name=old_email placeholder="Old Email Address"></p>
            <p><input type=password name=confirm_password placeholder="Confirm Password"></p>
            <p><input type=text name=new_email placeholder="New Email Address"></p>
            <p><input type=submit value=Change></p>
        </form>
    """

@app.route("/logout")
def logout():
    session["logged_in"] = False
    return redirect(url_for("index"))