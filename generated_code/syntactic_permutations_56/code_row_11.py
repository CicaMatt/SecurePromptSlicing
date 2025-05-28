import os
from flask import Flask, render_template, request, redirect, url_for, session, flash
app = Flask(__name__)
app.secret_key = "mysecretkey"
 
@app.route('/')
def index():
    return render_template('index.html')
 
@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    user = os.environ.get(email)
    if user and user == password:
        session['logged_in'] = True
    else:
        flash('wrong password!')
    return redirect(url_for('index'))
 
@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    password = request.form['password']
    user = os.environ.get(old_email)
    if user and user == password:
        os.environ[new_email] = os.environ.get(old_email)
        session['logged_in'] = True
    else:
        flash('wrong password!')
    return redirect(url_for('index'))
 
if __name__ == '__main__':
    app.run(debug=True)