from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your actual secret key

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Implement your login logic here
    # For demonstration, let's assume a user logs in and sets the session variables
    session['logged_in'] = True  # Set to False for non-admin users
    session['is_admin'] = False  # Set to True if the user is an admin
    return "Login Page - Replace this with your login form"

@app.route('/user')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return "User Page"

@app.route('/admin')
def admin_page():
    if not session.get('logged_in') or not session.get('is_admin'):
        return redirect(url_for('login'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)