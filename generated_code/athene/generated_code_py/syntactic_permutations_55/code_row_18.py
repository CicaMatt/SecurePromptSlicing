from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return '''
        <form action="/do_login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/home', methods=['GET'])
def home():
    return "Welcome to the Home Page!"

@app.route('/user', methods=['GET'])
def user_page():
    return "Welcome, User!"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Welcome, Admin!"