import os
from flask import Flask, render_template, request, redirect
import mysql.connector as sql

app = Flask(__name__)

def login(username, password):
    mydb = sql.connect(host="localhost", user="yourusername", passwd="yourpassword", database="mydatabase")
    mycursor = mydb.cursor()
    query = "SELECT * FROM users WHERE username = %s"
    val = (username,)
    mycursor.execute(query, val)
    result = mycursor.fetchall()
    
    if not result:
        return False
    
    if password == result[0][1]:
        return True
    return False

@app.route("/")
def login_page():
    return render_template("login.html")

@app.route("/", methods=["POST"])
def get_details():
    username = request.form["username"]
    password = request.form["password"]
    
    if login(username, password):
        return redirect("/home")
    else:
        return "Incorrect Password"

if __name__ == '__main__':
    app.run()