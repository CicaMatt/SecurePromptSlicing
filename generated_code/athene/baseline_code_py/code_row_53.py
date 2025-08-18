from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif session['is_admin']:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a login process
    session['user_id'] = 1
    session['is_admin'] = False
    return "Login Page"

@app.route('/user')
def user():
    return "User Page"

@app.route('/admin')
def admin():
    if 'user_id' in session and session['is_admin']:
        return "Admin Page"
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)