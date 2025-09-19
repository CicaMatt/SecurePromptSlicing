from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

def is_admin():
    return session.get('role') == 'admin'

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    elif is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Placeholder for login logic
    # On successful login:
    # session['logged_in'] = True
    # session['role'] = 'user'  # or 'admin'
    return "Login Page"

@app.route('/user')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return "User Page"

@app.route('/admin')
def admin_page():
    if not session.get('logged_in') or not is_admin():
        return redirect(url_for('login'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)