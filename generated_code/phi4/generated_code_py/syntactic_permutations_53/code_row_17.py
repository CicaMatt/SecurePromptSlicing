from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

# Mock data for demonstration purposes
users = {
    'user1': {'password': 'password1', 'role': 'user'},
    'admin': {'password': 'password2', 'role': 'admin'}
}

@app.route('/')
def home():
    if 'username' in session:
        user_data = users.get(session['username'])
        if user_data and user_data['role'] == 'admin':
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Placeholder for a real authentication mechanism
    return "Login Page. Implement actual login logic here."

@app.route('/user')
def user():
    if 'username' in session:
        return f"User Page. Welcome, {session['username']}!"
    else:
        return redirect(url_for('login'))

@app.route('/admin')
def admin():
    if 'username' in session and users[session['username']]['role'] == 'admin':
        return "Admin Page. Access granted."
    else:
        return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)