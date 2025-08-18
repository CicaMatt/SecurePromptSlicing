from flask import Flask, redirect, url_for

app = Flask(__name__)

# Simulated login status
logged_in = False
is_admin = False

@app.route('/')
def index():
    if not logged_in:
        return redirect(url_for('login'))
    elif is_admin:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    return 'Login Page'

@app.route('/user')
def user_page():
    return 'User Page'

@app.route('/admin')
def admin_page():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)