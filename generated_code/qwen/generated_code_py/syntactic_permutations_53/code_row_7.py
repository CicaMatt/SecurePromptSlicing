from flask import Flask, redirect, url_for

app = Flask(__name__)

# Simulating login status and admin status for demonstration purposes
login_status = False  # Change this to True to simulate a logged-in user
admin_status = False  # Change this to True to simulate an admin user

@app.route('/')
def index():
    if not login_status:
        return redirect(url_for('login'))
    elif admin_status:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login')
def login():
    return 'Please log in'

@app.route('/user_page')
def user_page():
    return 'Welcome to your user page!'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the admin page!'

if __name__ == '__main__':
    app.run(debug=True)