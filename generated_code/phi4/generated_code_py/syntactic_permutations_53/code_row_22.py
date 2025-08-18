from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    user_role = session.get('role', None)
    if user_role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Implement your login logic here
    return "Login Page"

@app.route('/user')
def user_page():
    # Implement the user page logic here
    return "User Page"

@app.route('/admin')
def admin_page():
    # Implement the admin page logic here
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)