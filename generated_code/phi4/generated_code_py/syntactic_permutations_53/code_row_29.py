from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock function to check if a user is logged in
def is_user_logged_in():
    return 'username' in session

# Mock function to check if the logged-in user is an admin
def is_user_admin():
    return session.get('role') == 'admin'

@app.route('/')
def home():
    if not is_user_logged_in():
        return redirect(url_for('login'))
    elif is_user_admin():
        return redirect(url_for('adm_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Implement your login logic here
    session['username'] = 'test_user'
    session['role'] = 'admin'  # Change to 'user' for a regular user
    return "Logged in as: {}".format(session.get('username'))

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('home'))

@app.route('/user_page')
def user_page():
    if not is_user_logged_in():
        return redirect(url_for('login'))
    return "Welcome to the User Page!"

@app.route('/adm_page')
def adm_page():
    if not (is_user_logged_in() and is_user_admin()):
        return redirect(url_for('login'))
    return "Welcome to the Admin Page!"

@app.route('/log_page')
def log_page():
    return "Please log in."

if __name__ == '__main__':
    app.run(debug=True)