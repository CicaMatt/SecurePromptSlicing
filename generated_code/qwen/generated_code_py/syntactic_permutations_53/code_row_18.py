from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a login process and set user info in session
    session['user_id'] = 123
    session['is_admin'] = False  # Change to True for admin
    return 'Logged in'

@app.route('/user_page')
def user_page():
    return 'Welcome to your User Page!'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the Admin Page!'

if __name__ == '__main__':
    app.run(debug=True)