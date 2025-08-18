from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock functions to simulate login status and user role checking.
def is_logged_in():
    return session.get('logged_in', False)

def is_admin():
    return session.get('role') == 'admin'

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    elif is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a user logging in
    session['logged_in'] = True
    session['role'] = 'user'  # Change to 'admin' if the user is an admin
    return "Login Successful"

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('role', None)
    return redirect(url_for('index'))

@app.route('/user_page')
def user_page():
    return "Welcome to the User Page!"

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)