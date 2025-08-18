from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif session.get('is_admin'):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Simulate a successful login
    session['user_id'] = 1
    session['is_admin'] = False  # Change to True to test admin redirection
    return 'Logged in successfully!'

@app.route('/user')
def user_page():
    return 'Welcome to your user page.'

@app.route('/admin')
def admin_page():
    return 'Welcome to the admin dashboard.'

if __name__ == '__main__':
    app.run(debug=True)