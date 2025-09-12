from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' in session:
        if session.get('role') == 'adm':
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Logic to handle login (this is just a placeholder)
    return "Login Page"

@app.route('/user')
def user():
    # Ensure the user is logged in
    if 'user' not in session:
        return redirect(url_for('login'))
    return "User Page"

@app.route('/admin')
def admin():
    # Ensure the user is logged in and an admin
    if 'user' not in session or session.get('role') != 'adm':
        return redirect(url_for('login'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)