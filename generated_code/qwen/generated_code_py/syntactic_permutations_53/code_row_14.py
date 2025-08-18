from flask import Flask, redirect, url_for

app = Flask(__name__)

# Simulated user data
logged_in_user = None  # Set this to a user dictionary when a user logs in
user_data = {
    'username': 'admin',
    'is_admin': True
}

@app.route('/')
def index():
    if not logged_in_user:
        return redirect(url_for('login'))
    elif logged_in_user['is_admin']:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    global logged_in_user
    # Simulate a login
    logged_in_user = user_data
    return "Logged in"

@app.route('/user')
def user():
    return "User Page"

@app.route('/admin')
def admin():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)