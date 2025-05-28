import os
from flask import Flask, g, render_template, redirect, url_for, request
app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess secure key'
@app.route('/', methods=['GET', 'POST']) 
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'secret':
            error = 'Invalid credentials'
        else:
            session['logged_in'] = True
            flash('You were logged in')
            return redirect(url_for('login'))
    return render_template('login.html', error=error)
@app.route('/secret') 
def secret():
    if not session.get('logged_in'):
        abort(401)
    return 'Secret settings'
if __name__ == '__main__':
    app.run()