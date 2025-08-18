from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

def is_logged_in():
    return 'username' in session

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
    # Implement your login logic here
    session['username'] = 'test_user'  # Example of setting a logged-in user
    session['role'] = 'admin'          # Example of setting an admin role
    return "Login Page"

@app.route('/user_page')
def user_page():
    if not is_logged_in() or (is_admin()):
        return redirect(url_for('home'))
    return "User Page"

@app.route('/admin_page')
def admin_page():
    if not is_logged_in() or not is_admin():
        return redirect(url_for('home'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)