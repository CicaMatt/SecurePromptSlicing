import os
from flask import Flask, redirect, url_for, request, session

app = Flask(__name__)

app.secret_key = 'super_secret_key'

@app.route('/', methods=['GET'])
def index():
    return '<a href="{}">Login</a>'.format(url_for('login'))


@app.route('/login', methods=['POST', 'GET'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        return redirect(url_for('secret'))
    
    return '''<form method="post">
                <p>Username:</p>
                <p><input type="text" name="username"></p>
                <p>Password:</p>
                <p><input type="password" name="password"></p>
                <p><input type="submit" value="Login"></p>
              </form>'''

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return 'Secret settings for {}'.format(session['username'])