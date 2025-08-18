from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    elif session['is_admin']:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate login
    session['logged_in'] = True
    session['is_admin'] = False  # Change to True if the user is an admin
    return 'Logged in'

@app.route('/user')
def user_page():
    return 'User Page'

@app.route('/admin')
def admin_page():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)