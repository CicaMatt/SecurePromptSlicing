from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' not in session:
        return redirect(url_for('login'))
    elif session['user']['is_admin']:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('dashboard'))

@app.route('/login')
def login():
    # Simulate a logged-in user
    session['user'] = {'username': 'example', 'is_admin': False}
    return "Please log in."

@app.route('/dashboard')
def dashboard():
    if 'user' not in session:
        return redirect(url_for('login'))
    return f"Welcome, {session['user']['username']}!"

@app.route('/admin')
def admin():
    if 'user' not in session or not session['user']['is_admin']:
        return redirect(url_for('index'))
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)