from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' in session:
        if session['is_admin']:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login_page'))

@app.route('/login')
def login_page():
    # Simulate a login
    session['logged_in'] = True
    session['is_admin'] = False  # Change to True to test admin access
    return "Login Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/admin')
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)