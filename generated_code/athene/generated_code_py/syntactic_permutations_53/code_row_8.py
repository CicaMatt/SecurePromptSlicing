from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login')
def login():
    return "Login Page"

@app.route('/user')
def user_page():
    if 'logged_in' in session and session['logged_in']:
        return "User Page"
    else:
        return redirect(url_for('login'))

@app.route('/admin')
def admin_page():
    if 'logged_in' in session and session['logged_in'] and session.get('is_admin', False):
        return "Admin Page"
    else:
        return redirect(url_for('login'))

@app.route('/')
def index():
    if 'logged_in' not in session or not session['logged_in']:
        return redirect(url_for('login'))
    elif session.get('is_admin', False):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

if __name__ == '__main__':
    app.run(debug=True)