import os
from flask import Flask, request, redirect, url_for, render_template
app = Flask(__name__)
app.config['DEBUG'] = True
@app.route('/')
def index():
    if not 'username' in session:
        return redirect(url_for('login'))
    else:
        if session['username']=='admin':
            return render_template("admin.html")
        return render_template("user.html", user=session['username'])
@app.route('/login', methods = ['GET', 'POST'])
def login():
    if request.method == 'POST' and 'username' in request.form:
        session['username'] = request.form['username']
        return redirect(url_for('index'))
    return render_template("login.html")
@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))
if __name__ == '__main__':
    app.run()