from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def is_logged_in():
    return 'user' in session

def is_admin():
    return session.get('role') == 'admin'

@app.route('/')
def home():
    if not is_logged_in():
        return redirect(url_for('login'))
    elif is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Here should be the logic for handling login
    return "Login Page"

@app.route('/user')
def user_page():
    if not is_logged_in():
        return redirect(url_for('login'))
    return "User Page"

@app.route('/admin')
def admin_page():
    if not is_logged_in() or not is_admin():
        return redirect(url_for('login'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)