from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['logged_in'] and 'admin' in session and session['admin']:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate login
    session['logged_in'] = True
    session['admin'] = False
    return "Login Page"

@app.route('/user')
def user():
    return "User Page"

@app.route('/admin')
def admin():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)