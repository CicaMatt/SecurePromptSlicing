from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'username' in session:
        if session['role'] == 'admin':
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    return redirect(url_for('login'))

@app.route('/login')
def login():
    # Implement your login logic here
    # For example purposes, setting a dummy user and role
    session['username'] = 'test_user'
    session['role'] = 'user'  # or 'admin' for admin access
    return "Logged in as: " + session['username']

@app.route('/user')
def user():
    if 'username' not in session:
        return redirect(url_for('login'))
    return "Welcome to the User page, " + session['username'] + "!"

@app.route('/admin')
def admin():
    if 'username' not in session or session.get('role') != 'admin':
        return redirect(url_for('login'))
    return "Welcome to the Admin page, " + session['username'] + "!"

if __name__ == '__main__':
    app.run(debug=True)