from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    
    user_role = session.get('role', None)
    if user_role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Dummy check for login
    # In a real application, you should verify credentials and set these values accordingly
    session['user_id'] = 1
    session['role'] = 'user'  # Change this to 'admin' if the user is an admin
    
    return "Logged in. Redirecting..."

@app.route('/user_page')
def user_page():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    
    return "Welcome, User!"

@app.route('/admin_page')
def admin_page():
    if 'user_id' not in session or session.get('role') != 'admin':
        return redirect(url_for('login'))

    return "Welcome, Admin!"

if __name__ == '__main__':
    app.run(debug=True)