from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['role'] == 'admin':
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a login process
    session['logged_in'] = True
    session['role'] = 'user'  # or 'admin'
    return "Login successful"

@app.route('/user')
def user():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return "User page"

@app.route('/admin')
def admin():
    if not session.get('logged_in') or session['role'] != 'admin':
        return redirect(url_for('login'))
    return "Admin page"

if __name__ == '__main__':
    app.run(debug=True)