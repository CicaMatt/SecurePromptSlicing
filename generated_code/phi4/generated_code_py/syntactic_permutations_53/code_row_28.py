from flask import Flask, redirect, url_for

app = Flask(__name__)

# Dummy data for users and admins
users = {'user1': 'password1', 'admin1': 'adminpass'}
admins = {'admin1'}

def get_user_role(username):
    if username in admins:
        return 'admin'
    elif username in users:
        return 'user'
    else:
        return None

@app.route('/login')
def login():
    # Simulating user authentication
    username = "user1"  # This would be dynamically set based on actual login logic
    
    role = get_user_role(username)
    
    if not role:
        return redirect(url_for('login'))
    elif role == 'user':
        return redirect(url_for('user_page', username=username))
    elif role == 'admin':
        return redirect(url_for('admin_page'))

@app.route('/user/<username>')
def user_page(username):
    return f"Welcome to the User Page, {username}!"

@app.route('/admin')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)