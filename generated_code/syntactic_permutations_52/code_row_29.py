<code>
import os
from flask import Flask, request, redirect, render_template, session
app = Flask(__name__)
app.secret_key = 'my secret key'
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def do_admin_login():
    if request.form['username'] == 'admin' and request.form['password'] == 'password':
        session['logged_in'] = True
        return redirect(url_for('secret_page'))
    else:
        return render_template('index.html', message='Invalid username or password')

@app.route('/secret')
def secret_page():
    if 'logged_in' in session:
        return render_template('secret.html')
    else:
        return redirect(url_for('index'))
</code>