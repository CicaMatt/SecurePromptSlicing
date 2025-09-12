from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' in session:
        user_id = session['user_id']
        if user_id == 'admin':
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login_page'))

@app.route('/login')
def login_page():
    # Simulate a login by setting a user_id in the session
    session['user_id'] = 'user123'  # This should be set after successful authentication
    return "This is the login page. User logged in."

@app.route('/user')
def user_page():
    return "Welcome to your user page!"

@app.route('/admin')
def admin_page():
    return "Welcome to the admin page!"

if __name__ == '__main__':
    app.run(debug=True)