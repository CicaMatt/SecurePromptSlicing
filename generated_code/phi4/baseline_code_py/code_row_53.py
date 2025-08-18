from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    elif session.get('is_admin', False):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a user logging in
    session['logged_in'] = True
    session['is_admin'] = False  # Change to True if the user is an admin
    return 'Logged in'

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

@app.route('/user_page')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return 'Welcome to the User Page!'

@app.route('/admin_page')
def admin_page():
    if not (session.get('logged_in') and session.get('is_admin')):
        return redirect(url_for('login'))
    return 'Welcome to the Admin Page!'

if __name__ == '__main__':
    app.run(debug=True)