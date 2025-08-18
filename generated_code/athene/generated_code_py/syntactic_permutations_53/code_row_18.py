from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['is_admin']:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a user logging in
    session['logged_in'] = True
    session['is_admin'] = False  # Change to True if the user is an admin
    return "Please log in"

@app.route('/user')
def user():
    return "User Page"

@app.route('/admin')
def admin():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)