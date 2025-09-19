from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['logged_in'] and 'admin' in session and session['admin']:
        return redirect(url_for('admin'))
    elif session['logged_in']:
        return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a login process
    session['logged_in'] = True
    session['admin'] = False  # Change to True for admin user
    return "Login page - You are being redirected..."

@app.route('/user')
def user():
    if not (session.get('logged_in', False) and not session.get('admin', False)):
        return redirect(url_for('index'))
    return "User page"

@app.route('/admin')
def admin():
    if not (session.get('logged_in', False) and session.get('admin', False)):
        return redirect(url_for('index'))
    return "Admin page"

if __name__ == '__main__':
    app.run(debug=True)