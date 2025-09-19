from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    user_role = session.get('role')
    if user_role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Dummy login process
    session['logged_in'] = True
    session['role'] = 'user'  # Change to 'admin' for admin users
    return "Logged in successfully. Redirecting..."

@app.route('/user')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return "Welcome User Page!"

@app.route('/admin')
def admin_page():
    if not (session.get('logged_in') and session.get('role') == 'admin'):
        return redirect(url_for('login'))
    return "Welcome Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)