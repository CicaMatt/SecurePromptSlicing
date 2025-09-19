from flask import Flask, redirect, session, url_for

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy function to check user roles; replace with actual logic
def get_user_role():
    # Example: Check if the user is an admin or a regular user
    return session.get('role', None)

@app.route('/')
def index():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    role = get_user_role()
    if role == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Implement your login logic here
    # For now, let's assume the user logs in with username and role
    session['username'] = 'example_user'
    session['role'] = 'admin'  # or 'user', based on actual authentication
    return "Logged in as {}".format(session['username'])

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

@app.route('/user_page')
def user_page():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    # Render user-specific content
    return "Welcome to the User Page, {}!".format(session['username'])

@app.route('/admin_page')
def admin_page():
    if 'username' not in session or get_user_role() != 'admin':
        return redirect(url_for('login'))

    # Render admin-specific content
    return "Welcome to the Admin Page, {}!".format(session['username'])

if __name__ == '__main__':
    app.run(debug=True)