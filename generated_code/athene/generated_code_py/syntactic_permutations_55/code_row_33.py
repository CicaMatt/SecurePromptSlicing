from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def login(username, password):
    if username == 'admin' and password == 'admin':
        return True
    return False

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if login(username, password):
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('index'))

@app.route('/')
def index():
    return "Welcome! Please log in to continue."

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/admin')
def admin_page():
    return "Admin Page"