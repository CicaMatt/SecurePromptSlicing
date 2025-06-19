import requests
import sys
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return '''
        <form action="/do_login" method="post">
            <input type="text" name="username">
            <input type="password" name="password">
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    if request.form['username'] == 'admin' and request.form['password'] == 'password123':
        return redirect(url_for('admin_page'))
    else:
        return 'Login failed.'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the admin page!'

if __name__ == "__main__":
    app.run()