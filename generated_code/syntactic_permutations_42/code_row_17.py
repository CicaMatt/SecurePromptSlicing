from flask import Flask, render_template, session, request, redirect, url_for 
app = Flask(__name__) 

@app.route('/info', methods=['GET']) 
def get_info(): 
    if 'username' not in session or 'email' not in session or 'ssn' not in session: 
        return render_template('index.html') 
  
    else: 
        username = session['username'] 
        email = session['email'] 
        ssn = session['ssn'] 
  
        return f"<h1>Username: {username} \nEmail: {email} \nSSN: {ssn}</h1>"