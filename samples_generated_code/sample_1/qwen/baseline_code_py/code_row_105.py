from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif 'is_admin' in session and session['is_admin']:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a login
    session['user_id'] = 1
    session['is_admin'] = False  # Change this to True to simulate an admin login
    return 'Logged in'

@app.route('/user_page')
def user_page():
    return 'User Page'

@app.route('/admin_page')
def admin_page():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)