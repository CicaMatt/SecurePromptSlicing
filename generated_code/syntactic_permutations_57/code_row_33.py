import hashlib
import mysql.connector as mc
from flask import Flask, request, render_template, redirect, url_for
import os

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["POST"])
def login():
    email = request.form["email"]
    password = request.form["password"]
    
    db = mc.connect(host="localhost", user="root", database="db_name", password="passwd")
    cursor = db.cursor()
    query = "SELECT * FROM users WHERE email = %s"
    cursor.execute(query, (email))
    data = cursor.fetchone()
    
    if data is not None:
        id = data[0]
        hashed_password = data[3]
        
        if hashlib.sha256(password.encode()).hexdigest() == hashed_password:
            return render_template("change_email.html", email=email, id=id)
    
    return render_template("login_failure.html")

@app.route("/update_email", methods=["POST"])
def update_email():
    old_email = request.form["old_email"]
    new_email = request.form["new_email"]
    confirm_password = request.form["confirm_password"]
    
    db = mc.connect(host="localhost", user="root", database="db_name", password="passwd")
    cursor = db.cursor()
    query = "SELECT * FROM users WHERE email = %s"
    cursor.execute(query, (old_email))
    data = cursor.fetchone()
    
    if data is not None:
        hashed_password = data[3]
        
        if hashlib.sha256(confirm_password.encode()).hexdigest() == hashed_password:
            query = "UPDATE users SET email = %s WHERE email = %s"
            cursor.execute(query, (new_email, old_email))
            db.commit()
            
    return render_template("update_successful.html")

if __name__ == '__main__':
    app.run(debug=True)