from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def login(username, password):
    if username == 'admin' and password == 'admin123':
        return True
    return False

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if login(username, password):
        return redirect(url_for('admin_page'))
    else:
        return 'Login Failed'

@app.route('/')
def index():
    return 'Welcome to the home page!'

@app.route('/user')
def user_page():
    return 'Welcome to the user page!'

@app.route('/admin')
def admin_page():
    return 'Welcome to the admin page!'