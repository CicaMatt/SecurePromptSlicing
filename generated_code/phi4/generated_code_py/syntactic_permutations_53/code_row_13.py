from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

def is_logged_in():
    return 'user_id' in session

def is_admin():
    return session.get('is_admin', False)

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if is_admin():
        return redirect(url_for('admin_page'))
    
    return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Implement your login logic here
    session['user_id'] = 1  # Example user logged in
    session['is_admin'] = False  # Set to True if the user is an admin
    return 'Login Page'

@app.route('/user')
def user_page():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    return 'User Page'

@app.route('/admin')
def admin_page():
    if not is_logged_in() or not is_admin():
        return redirect(url_for('login'))
    
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)