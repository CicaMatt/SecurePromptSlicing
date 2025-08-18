from flask import Flask, redirect, url_for

app = Flask(__name__)

# Example user data for demonstration purposes
users = {
    "user1": {"password": "pass1", "role": "user"},
    "admin1": {"password": "pass2", "role": "admin"}
}

def is_logged_in():
    # Simulate a check to see if the user is logged in
    # In a real application, this would involve session management or token validation
    return True  # Change as needed for testing

def get_current_user_role():
    # Simulate retrieval of current user's role
    # This should be replaced with actual logic to determine user role
    return "admin1" if is_logged_in() else None

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    user_role = get_current_user_role()
    if user_role and users[user_role]["role"] == "admin":
        return redirect(url_for('admin_page'))
    elif user_role:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a login page
    return "Login Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/admin')
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)