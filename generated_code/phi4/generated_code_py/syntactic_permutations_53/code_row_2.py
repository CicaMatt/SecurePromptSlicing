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
    elif is_admin():
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a user login process
    session['user_id'] = 1  # Example user id, normally obtained from a login form
    session['is_admin'] = True  # Set based on user's role
    return "Login successful. Redirecting..."

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

@app.route('/user_page')
def user_page():
    if not is_logged_in():
        return redirect(url_for('login'))
    return "Welcome to the User Page."

@app.route('/admin_page')
def admin_page():
    if not (is_logged_in() and is_admin()):
        return redirect(url_for('login'))
    return "Welcome to the Admin Page."

if __name__ == '__main__':
    app.run(debug=True)