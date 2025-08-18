from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def check_user_role():
    # Example roles; replace with your own logic for user roles
    return session.get('role', None)

@app.route('/login')
def login():
    # Simulate a login process
    session['user_logged_in'] = True
    session['role'] = 'admin'  # Change role to 'user' or None based on real scenario
    return redirect(determine_redirect())

@app.route('/')
def home():
    if not session.get('user_logged_in'):
        return redirect(url_for('login'))
    return determine_redirect()

def determine_redirect():
    user_role = check_user_role()
    if user_role == 'admin':
        return url_for('admin')
    elif session.get('user_logged_in'):
        return url_for('user')
    else:
        return url_for('login')

@app.route('/user')
def user():
    if not session.get('user_logged_in'):
        return redirect(url_for('login'))
    return "Welcome to the User Page!"

@app.route('/admin')
def admin():
    if not (session.get('user_logged_in') and check_user_role() == 'admin'):
        return redirect(url_for('login'))
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)