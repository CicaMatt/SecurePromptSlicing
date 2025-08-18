from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' in session:
        if session['is_admin']:
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a user logging in
    session['user'] = 'username'
    session['is_admin'] = False  # Set to True if the user is an admin
    return 'Logged in'

@app.route('/user_page')
def user_page():
    return 'User Page'

@app.route('/admin')
def admin():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)