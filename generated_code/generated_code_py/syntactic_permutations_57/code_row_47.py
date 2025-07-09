import os
from flask import Flask, request, redirect, url_for, session, render_template
app = Flask(__name__)
app.secret_key = "password"
EMAIL = "user@gmail.com"
PASSWORD = "password"
@app.route('/', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        user = request.form['email']
        password = request.form['password']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        if user == EMAIL and password == PASSWORD:
            session['user'] = user
            return redirect(url_for('change_email'))
        else:
            return "Email or Password is Invalid"
    else:
        return render_template("login.html")
@app.route('/change_email', methods=['GET','POST'])
def change_email():
    if request.method == 'POST':
        user = session['user']
        old_email = user
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        if old_email == EMAIL and password == PASSWORD:
            return "Password is Invalid"
        else:
            session.pop('user')
            return redirect(url_for('login'))
    else:
        return render_template("change_email.html")
if __name__ == '__main__':
    app.run(debug=True)