import os
from flask import Flask, redirect, url_for, request
app = Flask(__name__)
@app.route('/', methods=['GET'])
def login():
    return 'login'
@app.route('/login', methods=['POST'])
def post():
    username = request.form['username']
    password = request.form['password']
    if username and password in database:
        return redirect(url_for('success'))
    else:
        return redirect(url_for('cant_login'))
@app.route('/success')
def success():
    return 'logged in successfully'
@app.route('/cant_login')
def cant_login():
    return 'incorrect username or password'
@app.errorhandler(500)
def internal_server_error(e):
    return "An internal server error occurred", 500