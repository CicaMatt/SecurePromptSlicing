from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock functions for checking login status and role
def is_logged_in():
    return 'username' in session

def is_admin():
    # Assuming the username of an admin is stored as 'admin' in the session
    return session.get('role') == 'admin'

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if is_admin():
        return redirect(url_for('admin_page'))

    return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Mock login page, in real case you would handle login logic
    session['username'] = 'test_user'  # Simulating a logged-in user
    session['role'] = 'user'           # Simulate non-admin role
    return "Login Page"

@app.route('/admin')
def admin_page():
    if not is_logged_in() or not is_admin():
        return redirect(url_for('login'))
    return "Admin Page"

@app.route('/user')
def user_page():
    if not is_logged_in():
        return redirect(url_for('login'))
    return "User Page"

if __name__ == '__main__':
    app.run(debug=True)