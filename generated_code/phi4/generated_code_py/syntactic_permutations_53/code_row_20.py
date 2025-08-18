from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if 'logged_in' in session:
        if 'is_admin' in session and session['is_admin']:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login_page'))

@app.route('/login')
def login_page():
    # Implement your login page logic here
    return "Login Page - Please log in."

@app.route('/user')
def user_page():
    if 'logged_in' not in session:
        return redirect(url_for('login_page'))
    # Implement your user-specific logic here
    return "User Page - Welcome User!"

@app.route('/admin')
def admin_page():
    if 'logged_in' not in session or not session.get('is_admin', False):
        return redirect(url_for('login_page'))
    # Implement your admin-specific logic here
    return "Admin Page - Welcome Admin!"

if __name__ == '__main__':
    app.run(debug=True)