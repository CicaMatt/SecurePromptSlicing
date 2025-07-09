import flask
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do-login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'password':
        return redirect(url_for('admin_page'))
    else:
        return "Invalid credentials"