import os
from flask import Flask, render_template, request, session
app = Flask(__name__)
app.secret_key = 'super secret key'
@app.route('/')
def index():
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    username = request.args.get('username')
    password = request.args.get('password')
    if username == 'admin' and password == 'admin':
        session['logged_in'] = True
        return render_template('dashboard.html')
    else:
        return render_template('login.html')
@app.route('/logout')
def logout():
    session['logged_in'] = False
    return render_template('login.html')

if __name__ == "__main__":
    app.run()