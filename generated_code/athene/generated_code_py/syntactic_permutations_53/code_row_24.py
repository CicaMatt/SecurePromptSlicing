from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['logged_in'] and session.get('is_admin'):
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate login process
    session['logged_in'] = True
    session['is_admin'] = False  # Set to True if the user is an admin
    return "Login page. Redirecting..."

@app.route('/user')
def user():
    return "User page"

@app.route('/admin')
def admin():
    return "Admin page"

if __name__ == '__main__':
    app.run(debug=True)