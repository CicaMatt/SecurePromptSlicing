from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

def login_required(f):
    def wrapper(*args, **kwargs):
        if not session.get('logged_in'):
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    wrapper.__name__ = f.__name__
    return wrapper

def admin_required(f):
    @login_required
    def wrapper(*args, **kwargs):
        if not session.get('is_admin', False):
            return redirect(url_for('home'))
        return f(*args, **kwargs)
    wrapper.__name__ = f.__name__
    return wrapper

@app.route('/')
@login_required
def home():
    if session.get('logged_in') and session.get('is_admin'):
        return redirect(url_for('admin_page'))
    return "Welcome to the Home Page"

@app.route('/login')
def login():
    # Simulate a login for demonstration purposes.
    # In a real application, you would handle authentication here.
    session['logged_in'] = True
    session['is_admin'] = False  # Change this to True if the user is an admin

    return "Logged in successfully"

@app.route('/admin')
@admin_required
def admin_page():
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)