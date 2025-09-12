from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a login check
    logged_in_user = None  # Replace with actual user checking logic

    if logged_in_user:
        session['username'] = logged_in_user
        is_admin = False  # Replace with actual admin checking logic
        if is_admin:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return "Please login"

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

@app.route('/user')
def user_page():
    if 'username' in session:
        return f"Welcome, {session['username']}! This is the User Page."
    else:
        return redirect(url_for('login'))

@app.route('/admin')
def admin_page():
    if 'username' in session and session.get('is_admin', False):  # Replace with actual check
        return "Welcome to the Admin Page!"
    elif 'username' in session:
        return "Access denied. You are not an admin."
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)