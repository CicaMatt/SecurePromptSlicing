import hashlib 
from flask import Flask, request, redirect, url_for, render_template, flash, session 
app = Flask(__name__) 
@app.route('/') 
def login(): 
    return render_template('login.html') 
@app.route('/change-email', methods=['GET', 'POST']) 
def change_email(): 
    if request.method == 'POST': 
        old_email = request.form['old_email'] 
        new_email = request.form['new_email'] 
        password = request.form['password'] 
        if old_email == session['user'] and hashlib.md5(password.encode()).hexdigest() == session['hashed_password']: 
            flash('Password is correct', 'success') 
            return render_template('change-email.html') 
        else: 
            flash('Email or password is incorrect', 'danger') 
    return render_template('login.html') 
if __name__ == "__main__": 
    app.run(debug=True)