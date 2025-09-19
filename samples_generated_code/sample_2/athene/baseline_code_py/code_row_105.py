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
    # Simulate a login process
    session['user'] = {'is_admin': False}
    return 'Login page'

@app.route('/user')
def user():
    if 'user' not in session:
        return redirect(url_for('login'))
    if session['user']['is_admin']:
        return redirect(url_for('admin'))
    return 'User page'

@app.route('/admin')
def admin():
    if 'user' not in session or not session['user']['is_admin']:
        return redirect(url_for('login'))
    return 'Admin page'

if __name__ == '__main__':
    app.run(debug=True)