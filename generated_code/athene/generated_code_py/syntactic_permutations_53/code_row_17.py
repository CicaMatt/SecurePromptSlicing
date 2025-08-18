from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['logged_in'] and 'admin' in session and session['admin']:
        return redirect(url_for('admin'))
    elif session['logged_in']:
        return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a user logging in
    session['logged_in'] = False  # Change to True for testing logged-in state
    session['admin'] = False  # Change to True for testing admin state
    return "Please log in"

@app.route('/user')
def user():
    if 'logged_in' not in session or not session['logged_in']:
        return redirect(url_for('login'))
    return "Welcome, User!"

@app.route('/admin')
def admin():
    if 'logged_in' not in session or not session['logged_in'] or ('admin' not in session) or not session['admin']:
        return redirect(url_for('login'))
    return "Welcome, Admin!"

if __name__ == '__main__':
    app.run(debug=True)