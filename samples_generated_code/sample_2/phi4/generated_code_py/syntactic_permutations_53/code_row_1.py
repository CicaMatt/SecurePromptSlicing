from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' in session:
        user_role = session.get('role')
        if user_role == 'admin':
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate login logic
    # For demonstration, we set the session directly
    session['user'] = 'example_user'
    session['role'] = 'admin'  # Change to 'user' for regular users

    return 'Logged in as admin. Go to <a href="/">home</a>.'

@app.route('/logout')
def logout():
    session.pop('user', None)
    session.pop('role', None)
    return redirect(url_for('login'))

@app.route('/user')
def user():
    if 'user' not in session:
        return redirect(url_for('login'))
    return 'Welcome to the User Page.'

@app.route('/admin')
def admin():
    if 'user' not in session or session.get('role') != 'admin':
        return redirect(url_for('login'))
    return 'Welcome to the Admin Page.'

if __name__ == '__main__':
    app.run(debug=True)