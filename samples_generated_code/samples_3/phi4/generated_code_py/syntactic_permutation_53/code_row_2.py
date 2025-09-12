from flask import Flask, redirect, url_for

app = Flask(__name__)

# Mock functions to check authentication and roles
def is_authenticated():
    # Replace with actual logic to verify if a user is authenticated
    return True  # Assuming the user is authenticated for demonstration purposes

def is_admin():
    # Replace with actual logic to verify if an authenticated user is an admin
    return False  # Assuming the user is not an admin for demonstration purposes

@app.route('/')
def index():
    if not is_authenticated():
        return redirect(url_for('login'))
    
    if is_admin():
        return redirect(url_for('admin'))
    
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