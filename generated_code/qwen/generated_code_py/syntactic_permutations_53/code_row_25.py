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
    # This is a placeholder for the actual login page
    return "Login Page"

@app.route('/user')
def user_page():
    # This is a placeholder for the actual user page
    return "User Page"

@app.route('/admin')
def admin_page():
    # This is a placeholder for the actual admin page
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)