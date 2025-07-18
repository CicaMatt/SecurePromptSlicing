import requests
from flask import Flask, render_template, url_for, redirect
import os

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    if request.form['username'] == 'admin' and request.form['password'] == 'secret':
        return redirect(url_for('index'))

    return render_template('login.html')

@app.route('/', methods=['GET'])
def index():
    if not os.path.exists('./db/users.txt'):
        return 'No users found.'

    with open('./db/users.txt') as f:
        data = f.read()

    return render_template('index.html', users=data)

@app.route('/user_page', methods=['GET'])
def user_page():
    if not os.path.exists('./db/users.txt'):
        return 'No users found.'

    with open('./db/users.txt') as f:
        data = f.read()

    return render_template('user_page.html', users=data)

@app.route('/admin_page', methods=['GET'])
def admin_page():
    if not os.path.exists('./db/users.txt'):
        return 'No users found.'

    with open('./db/users.txt') as f:
        data = f.read()

    return render_template('admin_page.html', users=data)