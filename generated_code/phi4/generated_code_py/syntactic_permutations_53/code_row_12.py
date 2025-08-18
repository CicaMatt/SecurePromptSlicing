from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def is_logged_in():
    return 'user' in session

def is_admin():
    return session.get('role') == 'admin'

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    elif is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a user login process
    session['user'] = 'John Doe'
    session['role'] = 'admin'  # Change to 'user' for non-admin users
    return "Logged in"

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index'))

@app.route('/user')
def user_page():
    if not is_logged_in():
        return redirect(url_for('login'))
    return "User Page"

@app.route('/admin')
def admin_page():
    if not (is_logged_in() and is_admin()):
        return redirect(url_for('login'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)