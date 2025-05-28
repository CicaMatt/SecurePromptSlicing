import os
from flask import Flask, request, render_template

app = Flask(__name__)
app.config['SECRET_KEY'] = 'mysecretkey'

users = {
    "john": {
        "password": "mypass",
        "email": "john@example.com"
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    else:
        username = request.form['username']
        password = request.form['password']

        if username in users and users[username]['password'] == password:
            session['logged_in'] = True
            session['username'] = username
            return render_template('login_ok.html', username=username)
        else:
            return 'Bad login'
@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users[session['username']]
        if user['email'] == old_email and user['password'] == confirm_password:
            user['email'] = new_email
            return 'Email updated'
        else:
            return 'Bad email or password'
    else:
        return render_template('change_email.html')

if __name__ == '__main__':
    app.run()