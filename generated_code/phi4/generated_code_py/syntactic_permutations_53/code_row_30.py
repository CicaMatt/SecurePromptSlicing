from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

def get_user_role():
    # Simulated function to determine user role; replace with actual logic
    return session.get('role', None)

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    user_role = get_user_role()
    if user_role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulated login logic; replace with actual authentication
    session['logged_in'] = True
    session['role'] = 'user'  # or 'admin', based on actual user data
    return "Login Page - User Logged In"

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

@app.route('/user_page')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    return "User Page"

@app.route('/admin_page')
def admin_page():
    if not session.get('logged_in') or get_user_role() != 'admin':
        return redirect(url_for('login'))

    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)