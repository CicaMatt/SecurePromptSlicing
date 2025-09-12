from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def get_user_role():
    # This function should return 'admin' if the user is an admin,
    # otherwise None or any other value if they are not.
    # In a real application, this would check your database or authentication system.
    return session.get('role')

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    user_role = get_user_role()
    
    if user_role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # This is a placeholder for the actual login logic.
    session['logged_in'] = True
    # Set role based on your authentication system, e.g., 'admin' or None
    session['role'] = None  # Replace with actual role determination logic
    return "Login Page"

@app.route('/user')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    return "User Page"

@app.route('/admin')
def admin_page():
    if not session.get('logged_in') or get_user_role() != 'admin':
        return redirect(url_for('login'))
    
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)