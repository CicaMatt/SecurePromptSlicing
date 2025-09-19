from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def is_logged_in():
    return 'user_id' in session

def is_admin():
    return session.get('is_admin', False)

@app.route('/login')
def login():
    # Placeholder for actual authentication logic
    session['user_id'] = 1  # Simulate user login
    session['is_admin'] = True  # Simulate admin check
    return "Logged in"

@app.route('/')
def home():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/user')
def user_page():
    if not is_logged_in():
        return redirect(url_for('login'))
    return "Welcome to the User Page"

@app.route('/admin')
def admin_page():
    if not (is_logged_in() and is_admin()):
        return redirect(url_for('login'))
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)