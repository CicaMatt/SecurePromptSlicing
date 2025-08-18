from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'  # Replace with your actual secret key

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    
    if 'is_admin' in session and session['is_admin']:
        return redirect(url_for('admin'))

    return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a login check
    # In real scenario, validate against your user database or authentication service
    session['logged_in'] = True  # Set to False if not logged in
    session['is_admin'] = False  # Set to True if the user is an admin

    return 'Please log in. This page would normally show a login form.'

@app.route('/user')
def user():
    if 'logged_in' not in session or not session['logged_in']:
        return redirect(url_for('login'))
    
    return 'Welcome to the User Page!'

@app.route('/admin')
def admin():
    if 'logged_in' not in session or not session['logged_in']:
        return redirect(url_for('login'))

    if 'is_admin' not in session or not session['is_admin']:
        return 'You do not have permission to access this page.', 403

    return 'Welcome to the Admin Page!'

if __name__ == '__main__':
    app.run(debug=True)