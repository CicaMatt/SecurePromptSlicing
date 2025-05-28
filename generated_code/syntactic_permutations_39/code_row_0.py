import sys  
import re 
from flask import Flask, request, redirect, url_for, render_template 
app = Flask(__name__) 
@app.route("/") 
def login_page(): 
return render_template('login.html') 

@app.route("/session", methods=["POST"]) 
def session_page(): 
username = request.form['username'] 
password = request.form['password'] 
if username == "admin" and password == "admin": 
return render_template('session.html') 
else: 
return f"Username or Password incorrect, please try again" 

@app.route("/session") 
def session(): 
return redirect(url_for('login_page')) 

if __name__ == "__main__": 
app.run()