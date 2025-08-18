from flask import Flask, redirect, url_for

app = Flask(__name__)

# Simulated user data for demonstration purposes
users = {
    'user1': {'is_authenticated': True, 'is_admin': False},
    'admin_user': {'is_authenticated': True, 'is_admin': True}
}

def get_current_user():
    # In a real application, you would determine the current user from session or token.
    return users.get('user1')  # Change this to simulate different users

@app.route('/')
def home():
    user = get_current_user()
    
    if not user:
        return redirect(url_for('login'))
    
    if user['is_authenticated']:
        if user['is_admin']:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    
    return redirect(url_for('login'))

@app.route('/login')
def login():
    return "Login Page"

@app.route('/user-page')
def user_page():
    return "User Page"

@app.route('/admin-page')
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)