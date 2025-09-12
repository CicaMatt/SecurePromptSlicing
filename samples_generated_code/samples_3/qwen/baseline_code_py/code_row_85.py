from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' in session:
        if session.get('is_admin'):
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login_page'))

@app.route('/login')
def login_page():
    # Simulate a login process
    session['user_id'] = 12345
    session['is_admin'] = False  # Change to True for admin testing
    return "Logged in successfully!"

@app.route('/user')
def user_page():
    if 'user_id' not in session:
        return redirect(url_for('login_page'))
    return "Welcome to the User Page!"

@app.route('/admin')
def admin_page():
    if 'user_id' not in session or not session.get('is_admin'):
        return redirect(url_for('login_page'))
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)