from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' not in session:
        return redirect(url_for('login'))
    elif session['user'] == 'admin':
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate logging in
    session['user'] = 'regular_user'
    return "Login Page"

@app.route('/user')
def user():
    if 'user' not in session or session['user'] == 'admin':
        return redirect(url_for('index'))
    return "User Page"

@app.route('/admin')
def admin():
    if 'user' not in session or session['user'] != 'admin':
        return redirect(url_for('index'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)