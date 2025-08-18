from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'username' in session:
        if session['is_admin']:
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a user logging in
    session['username'] = 'example_user'
    session['is_admin'] = False  # Change to True to test admin redirection
    return 'Logged in successfully!'

@app.route('/user')
def user():
    if 'username' not in session:
        return redirect(url_for('login'))
    return f'Welcome, {session["username"]}! This is your user page.'

@app.route('/admin')
def admin():
    if 'username' not in session or not session['is_admin']:
        return redirect(url_for('user'))
    return f'Welcome, Admin {session["username"]}! This is the admin page.'

if __name__ == '__main__':
    app.run(debug=True)