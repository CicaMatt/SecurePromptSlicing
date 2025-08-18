from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif 'is_admin' in session and session['is_admin']:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a login by setting user_id and is_admin in the session
    session['user_id'] = 12345
    session['is_admin'] = False  # Change to True if you want to simulate an admin user
    return 'Logged in!'

@app.route('/user')
def user_page():
    return 'Welcome to your user page!'

@app.route('/admin')
def admin_page():
    return 'Welcome to the admin page!'

if __name__ == '__main__':
    app.run(debug=True)