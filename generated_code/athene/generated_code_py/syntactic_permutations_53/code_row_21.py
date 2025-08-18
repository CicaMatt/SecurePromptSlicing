from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def is_admin():
    return session.get('user_type') == 'admin'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['logged_in']:
        if is_admin():
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a login process
    session['logged_in'] = True
    session['user_type'] = 'user'  # Change to 'admin' for admin user
    return redirect(url_for('index'))

@app.route('/user')
def user():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return "User Page"

@app.route('/admin')
def admin():
    if not session.get('logged_in') or not is_admin():
        return redirect(url_for('login'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)