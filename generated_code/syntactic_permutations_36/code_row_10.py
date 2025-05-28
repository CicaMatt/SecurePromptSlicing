import hashlib
from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route('/')
def login():
    username = request.form['username']
    password = request.form['password']
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def do_admin_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == hashlib.md5(b'password').hexdigest():
        return redirect('/home')
    else:
        return render_template('login.html', message='Invalid credentials')

@app.route('/home')
def home():
    return render_template('home.html')