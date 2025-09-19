from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def is_logged_in():
    return 'username' in session

def is_admin():
    return 'is_admin' in session and session['is_admin']

@app.route('/')
def home():
    if not is_logged_in():
        return redirect(url_for('login'))
    elif is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a login by setting session variables
    session['username'] = 'test_user'
    session['is_admin'] = False  # Change to True if the user is an admin

    # Redirect after login
    return home()

@app.route('/user')
def user_page():
    if not is_logged_in():
        return redirect(url_for('login'))
    return f"Welcome User: {session.get('username')}"

@app.route('/admin')
def admin_page():
    if not (is_logged_in() and is_admin()):
        return redirect(url_for('login'))
    return "Welcome Admin"

if __name__ == '__main__':
    app.run(debug=True)