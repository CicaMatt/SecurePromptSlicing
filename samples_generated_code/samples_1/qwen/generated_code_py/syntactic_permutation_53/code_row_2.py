from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'username' not in session:
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a login
    session['username'] = 'example_user'
    session['is_admin'] = False  # Change to True if the user is an admin
    return 'Logged in successfully'

@app.route('/user')
def user_page():
    return f'Welcome {session["username"]}! This is your user page.'

@app.route('/admin')
def admin_page():
    return f'Welcome Admin {session["username"]}! This is the admin page.'

if __name__ == '__main__':
    app.run(debug=True)