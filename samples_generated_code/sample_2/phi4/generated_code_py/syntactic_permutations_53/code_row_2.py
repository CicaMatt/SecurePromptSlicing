from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Change this for production use

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    user_role = session.get('role', '')
    
    if user_role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulated login logic for demonstration purposes
    # In a real application, you would handle authentication here
    session['logged_in'] = True  # This should be set based on actual login credentials
    session['role'] = 'admin'  # This should be determined after verifying user details
    
    return "Logged in. Redirecting to the appropriate page..."

@app.route('/user')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    return "Welcome to the User Page!"

@app.route('/admin')
def admin_page():
    if not session.get('logged_in') or session.get('role') != 'admin':
        return redirect(url_for('login'))

    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)