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
        return 'Invalid credentials'

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the homepage!"

@app.route('/about', methods=['GET'])
def about():
    return "This is the about page."

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Welcome to the admin page!"