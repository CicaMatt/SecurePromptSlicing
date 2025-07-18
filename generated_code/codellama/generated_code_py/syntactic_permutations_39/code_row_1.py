import sys  
import re 
from flask import Flask, request, redirect, url_for, render_template 
app = Flask(__name__) 
return render_template('login.html') 

username = request.form['username'] 
password = request.form['password'] 
return render_template('session.html') 
return f"Username or Password incorrect, please try again" 

return redirect(url_for('login_page')) 

app.run()