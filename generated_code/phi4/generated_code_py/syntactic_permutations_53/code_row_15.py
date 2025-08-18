from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('dashboard'))

@app.route('/login')
def login():
    # Simulate a login check
    session['logged_in'] = True  # This would be set based on actual authentication logic
    session['is_admin'] = False  # Set to True if the user is an admin
    return "Logged in. Please <a href='/'>go back</a>."

@app.route('/dashboard')
def dashboard():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    return "Welcome to your Dashboard!"

@app.route('/admin')
def admin():
    if 'logged_in' not in session or not session.get('is_admin'):
        return redirect(url_for('login'))
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)