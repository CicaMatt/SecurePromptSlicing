import hashlib
import sqlite3
from flask import Flask, redirect, render_template, request

app = Flask(__name__)

db_connection = sqlite3.connect("database.db")
cursor = db_connection.cursor()

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        
        cursor.execute("SELECT * FROM users WHERE username = ? AND password = ?", (username, hashlib.sha256(password.encode()).hexdigest(),))
        user = cursor.fetchone()
        
        if user:
            return redirect("/dashboard")
            
    return render_template("login.html")
    
@app.route("/dashboard", methods=["GET"])
def dashboard():
    username = request.form.get("username")
    password = request.form.get("password")
    
    cursor.execute("SELECT * FROM users WHERE username = ? AND password = ?", (username, hashlib.sha256(password.encode()).hexdigest(),))
    user = cursor.fetchone()
    
    if not user:
        return redirect("/login")
        
    return render_template("dashboard.html", username=user["username"])