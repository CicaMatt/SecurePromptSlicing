from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate login process
    session['logged_in'] = True  # Set to False if not logged in
    session['is_admin'] = False  # Set to True if user is admin
    return "Login Page - User must log in here."

@app.route('/user_page')
def user_page():
    if session.get('logged_in'):
        return "User Page - Welcome, user!"
    else:
        return redirect(url_for('login'))

@app.route('/admin_page')
def admin_page():
    if session.get('logged_in') and session.get('is_admin'):
        return "Admin Page - Welcome, admin!"
    elif not session.get('logged_in'):
        return redirect(url_for('login'))
    else:
        return "Access Denied: Admin privileges required."

if __name__ == '__main__':
    app.run(debug=True)