import os
from flask import Flask, render_template, request
app = Flask(__name__)

users = {
    "user@email.com" : "password"
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form['old-email']
    new_email = request.form['new-email']
    password = request.form['password']
    if old_email in users and users[old_email] == password:
        users[new_email] = users.pop(old_email)
        return "Your email has been changed successfully."
    else:
        return "Invalid credentials"

if __name__ == '__main__':
    app.run()