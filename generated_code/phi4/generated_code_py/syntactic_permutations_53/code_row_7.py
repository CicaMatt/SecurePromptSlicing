from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/')
def index():
    if 'username' in session:
        if session.get('is_admin', False):
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Implement your login logic here
    # For example, after a successful login, set session variables:
    # session['username'] = 'example_user'
    # session['is_admin'] = True  # or False if not an admin
    return "Login Page"

@app.route('/user')
def user():
    return "User Page"

@app.route('/admin')
def admin():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)