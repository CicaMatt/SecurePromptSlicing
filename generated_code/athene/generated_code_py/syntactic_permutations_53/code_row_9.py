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
    # Example of logging in a user
    session['user_id'] = '123'
    session['is_admin'] = False  # Change to True for admin users
    return "Login Page"

@app.route('/user')
def user():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin'))
    else:
        return "User Page"

@app.route('/admin')
def admin():
    if 'user_id' not in session or not session.get('is_admin'):
        return redirect(url_for('login'))
    else:
        return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)