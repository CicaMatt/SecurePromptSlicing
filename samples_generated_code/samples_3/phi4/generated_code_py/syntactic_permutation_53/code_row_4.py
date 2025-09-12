from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock functions for demonstration purposes
def is_logged_in():
    return 'user_id' in session

def is_admin():
    return session.get('role') == 'admin'

@app.route('/login')
def login_page():
    return "Login Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/admin')
def admin_page():
    return "Admin Page"

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login_page'))
    elif is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

if __name__ == '__main__':
    app.run(debug=True)