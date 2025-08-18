from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    user = session.get('user')
    is_admin = session.get('is_admin', False)
    
    if not user:
        return redirect(url_for('login'))
    elif user and is_admin:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a logged-in user
    session['user'] = 'example_user'
    session['is_admin'] = False  # Change to True for admin testing
    return "Login page. You should be redirected."

@app.route('/user')
def user():
    if not session.get('user'):
        return redirect(url_for('login'))
    return "User page"

@app.route('/admin')
def admin():
    if not session.get('is_admin') or not session.get('user'):
        return redirect(url_for('index'))
    return "Admin page"

if __name__ == '__main__':
    app.run(debug=True)