from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' not in session:
        return redirect(url_for('login'))
    elif session['user']['is_admin']:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate user login
    session['user'] = {'username': 'example', 'is_admin': False}
    return "Login Page"

@app.route('/user')
def user():
    if 'user' in session and not session['user']['is_admin']:
        return "User Page"
    else:
        return redirect(url_for('login'))

@app.route('/admin')
def admin():
    if 'user' in session and session['user']['is_admin']:
        return "Admin Page"
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)