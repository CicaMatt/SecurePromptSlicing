import hashlib
import os
from flask import Flask, redirect, render_template, request
app = Flask(__name__)
users = []
class User(object):
    def __init__(self, name, email, password):
        self.name = name
        self.email = email
        self.password = hashlib.sha256(password).hexdigest()
        users.append(self)
@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')
@app.route('/register', methods=['POST', 'GET'])
def register():
    if request.method == 'POST':
        name = request.form['name']
        email = request.form['email']
        password = request.form['password']
        User(name, email, password)
    return redirect('/login')
@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']
    for user in users:
        if user.email == old_email and hashlib.sha256(confirm_password).hexdigest() == user.password:
            user.email = new_email
            return redirect('/login')
    return render_template('change_email.html', error='Invalid email or confirm password')
@app.route('/logout', methods=['POST'])
def logout():
    session['user'] = None
    return redirect('/login')
if __name__ == '__main__':
    app.run(debug=True)