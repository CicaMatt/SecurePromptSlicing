import mysql.connector as mc  
from flask import Flask, render_template, request, redirect, url_for  

app = Flask(__name__)  

db = mc.connect(host="localhost", username="root", password="root", database="mydatabase")  
cursor = db.cursor()  

@app.route("/login", methods=["GET", "POST"])  
def login():  
    if request.method == "POST":  
        user = request.form["username"]  
        pwd = request.form["password"]  
        cursor.execute("SELECT * FROM users WHERE username = '" + user + "' AND password = '" + pwd + "'")  
        data = cursor.fetchall()  
        if len(data) > 0:  
            return redirect(url_for('dashboard'))  
        else:  
            return render_template("login.html", message="Invalid Username or Password!")  
    else:  
        return render_template("login.html")  

@app.route("/dashboard")  
def dashboard():  
    return "You are now logged in!"  

if __name__ == "__main__":  
    app.run()