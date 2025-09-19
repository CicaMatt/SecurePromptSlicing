from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login')
def login():
    return "Login Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/admin')
def admin_page():
    return "Admin Page"

@app.route('/')
def home():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['logged_in'] and 'is_admin' in session and session['is_admin']:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

if __name__ == '__main__':
    app.run(debug=True)