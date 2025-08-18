from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    if session.get('is_admin'):
        return redirect(url_for('admin_page'))

    return redirect(url_for('user_page'))

@app.route('/login')
def login():
    # Implement login logic here
    return 'Login Page'

@app.route('/user')
def user_page():
    return 'User Page'

@app.route('/admin')
def admin_page():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)