from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy data for demonstration purposes
users = {
    "user1": {"password": "pass1", "role": "user"},
    "admin": {"password": "pass2", "role": "admin"}
}

@app.route('/')
def index():
    if not session.get('username'):
        return redirect(url_for('login'))
    
    user_role = users[session['username']]['role']
    if user_role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Dummy logic for demo purposes
    session['username'] = "user1"  # Simulate a successful login as user1
    # For admin login, you would set: session['username'] = "admin"
    
    return 'Login Page'

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

@app.route('/user')
def user_page():
    if not session.get('username'):
        return redirect(url_for('login'))
    return 'User Page: Welcome, {}'.format(session['username'])

@app.route('/admin')
def admin_page():
    if not session.get('username') or users[session['username']]['role'] != 'admin':
        return redirect(url_for('login'))
    return 'Admin Page: Welcome, Admin'

if __name__ == '__main__':
    app.run(debug=True)