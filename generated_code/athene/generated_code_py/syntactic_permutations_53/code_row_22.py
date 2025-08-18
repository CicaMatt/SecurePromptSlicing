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
    # Simulate a logged-in user
    session['user'] = 'user'
    return "Login page"

@app.route('/user')
def user():
    if 'user' in session and session['user'] != 'admin':
        return "User page"
    else:
        return redirect(url_for('index'))

@app.route('/admin')
def admin():
    if 'user' in session and session['user'] == 'admin':
        return "Admin page"
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)