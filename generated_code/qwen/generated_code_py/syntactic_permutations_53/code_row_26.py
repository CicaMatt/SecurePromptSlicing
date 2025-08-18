from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_role' not in session:
        return redirect(url_for('login'))
    elif session['user_role'] == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a login by setting user role
    session['user_role'] = 'user'  # Change to 'admin' to test admin redirection
    return 'Logged in'

@app.route('/user')
def user_page():
    return 'User Page'

@app.route('/admin')
def admin_page():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)