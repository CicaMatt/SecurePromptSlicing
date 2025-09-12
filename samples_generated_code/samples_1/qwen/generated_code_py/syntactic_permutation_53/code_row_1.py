from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'username' in session:
        if session['username'] == 'admin':
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login_page'))

@app.route('/login')
def login_page():
    # Simulate a login by setting the username in the session
    session['username'] = 'user'  # or 'admin' to test admin redirection
    return 'Login Page'

@app.route('/user')
def user_page():
    return 'User Page'

@app.route('/admin')
def admin_page():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)