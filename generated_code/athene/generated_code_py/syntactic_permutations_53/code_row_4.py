from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def is_logged_in():
    return 'user_id' in session

def is_admin():
    return session.get('role') == 'admin'

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    elif is_admin():
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a login
    session['user_id'] = 1
    session['role'] = 'user'
    return "Please log in."

@app.route('/user')
def user():
    if not is_logged_in():
        return redirect(url_for('login'))
    return "User page"

@app.route('/admin')
def admin():
    if not is_logged_in() or not is_admin():
        return redirect(url_for('index'))
    return "Admin page"

if __name__ == '__main__':
    app.run(debug=True)