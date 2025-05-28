from flask import Flask, render_template, request
from flask_mail import Mail, Message
import psycopg2
from validate_email import validate_email
import hashlib
app = Flask(__name__)

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "GET":
        return render_template("login.html")
    
    old_email = request.form["old_email"]
    new_email = request.form["new_email"]
    password = request.form["password"]
    confirm_password = request.form["confirm_password"]

    if not validate_email(new_email):
        return render_template("login.html", error="Invalid email address")
    
    if not hashlib.md5(password.encode()).hexdigest() == user_data[0][1]:
        return render_template("login.html", error="Password is incorrect")
    
    if confirm_password != password:
        return render_template("login.html", error="Passwords do not match")

    if old_email == new_email:
        return render_template("login.html", error="Old email and new email cannot be the same")
    
    try:
        connection = psycopg2.connect(
            host= "localhost",
            database="postgres",
            user="postgres",
            password="password"
        )
        
        cursor = connection.cursor()
        cursor.execute("UPDATE users SET email = %s WHERE email = %s AND password = %s", (new_email, old_email, hashlib.md5(password.encode()).hexdigest()))
        connection.commit()
    
    except Exception as e:
        print(e)
        return render_template("login.html", error="Failed to update email")
    
    finally:
        if connection:
            cursor.close()
            connection.close()
    
    return render_template("login.html", success=True)