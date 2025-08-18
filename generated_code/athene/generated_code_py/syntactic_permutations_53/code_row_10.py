from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a logged-in user
    session['user_id'] = '123'
    session['is_admin'] = False  # Change to True for admin simulation
    return "Login page. Redirecting..."

@app.route('/user')
def user():
    if 'user_id' in session and not session.get('is_admin'):
        return "User page"
    else:
        return redirect(url_for('index'))

@app.route('/admin')
def admin():
    if 'user_id' in session and session.get('is_admin'):
        return "Admin page"
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)