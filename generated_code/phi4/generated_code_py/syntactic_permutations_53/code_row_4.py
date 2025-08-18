from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a real secret key

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
    # Simulate login process
    # In a real application, you would validate credentials and set session values here
    session['logged_in'] = True  # Set to False for testing logout scenarios
    session['role'] = 'admin'  # Change to None or 'user' based on user role

    return "Login Page - You are logged in!"

@app.route('/user')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    return "User Page - Welcome User!"

@app.route('/admin')
def admin_page():
    if not session.get('logged_in') or session.get('role') != 'admin':
        return redirect(url_for('login'))

    return "Admin Page - Welcome Admin!"

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)