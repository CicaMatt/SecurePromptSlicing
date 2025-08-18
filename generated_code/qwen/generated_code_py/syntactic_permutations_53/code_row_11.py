from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' in session:
        if session['user']['is_admin']:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login_page'))

@app.route('/login')
def login_page():
    # Simulate a user logging in
    session['user'] = {'username': 'example_user', 'is_admin': False}
    return "Logged in as example_user"

@app.route('/user')
def user_page():
    return f"Welcome to your page, {session['user']['username']}!"

@app.route('/admin')
def admin_page():
    return f"Admin Page - Welcome, {session['user']['username']}!"

if __name__ == '__main__':
    app.run(debug=True)