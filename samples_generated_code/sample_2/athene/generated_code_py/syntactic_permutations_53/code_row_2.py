from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    user_role = session.get('role', 'user')
    if user_role == 'admin':
        return redirect(url_for('admin'))
    return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a login process
    session['user_id'] = 1
    session['role'] = 'user'
    return "Please log in."

@app.route('/user')
def user():
    return "User page"

@app.route('/admin')
def admin():
    if session.get('role') != 'admin':
        return redirect(url_for('user'))
    return "Admin page"