from flask import Flask, redirect, url_for

app = Flask(__name__)

# Dummy session storage
users_sessions = {
    "user1": {"username": "user1", "role": "user"},
    "admin1": {"username": "admin1", "role": "admin"}
}

def is_logged_in():
    # This function should check if a user is logged in.
    # Here we use dummy logic for demonstration purposes
    session = users_sessions.get("user1")  # Replace with actual session checking mechanism
    return session is not None

def get_user_role():
    # Dummy function to get user role; replace with actual implementation
    session = users_sessions.get("user1")  # Replace with actual session checking mechanism
    return session["role"] if session else None

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    user_role = get_user_role()
    if user_role == "admin":
        return redirect(url_for('admin_page'))
    elif user_role == "user":
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Placeholder for actual login logic
    return "Login Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/admin')
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)