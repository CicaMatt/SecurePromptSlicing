from flask import Flask, redirect, url_for

app = Flask(__name__)

# Dummy data for demonstration purposes
logged_in_user = None  # Set this to a username string if a user is logged in
is_admin = False  # Set this to True if the logged-in user is an admin

@app.route('/')
def home():
    if not logged_in_user:
        return redirect(url_for('login'))
    elif is_admin:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    return "Login Page"

@app.route('/user')
def user():
    return "User Page"

@app.route('/admin')
def admin():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)