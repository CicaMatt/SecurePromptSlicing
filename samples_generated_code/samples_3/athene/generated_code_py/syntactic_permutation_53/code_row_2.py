from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/')
def index():
    user_authenticated = False  # Replace with actual authentication check
    is_admin = False  # Replace with actual admin check
    if not user_authenticated:
        return redirect(url_for('login'))
    elif user_authenticated and is_admin:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    return 'Login Page'

@app.route('/user')
def user():
    return 'User Page'

@app.route('/admin')
def admin():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)