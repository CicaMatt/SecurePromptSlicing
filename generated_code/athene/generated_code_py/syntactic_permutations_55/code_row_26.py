from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return '''
        <form method="post" action="/do_login">
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
    elif username and password:
        return redirect(url_for('user_page', user=username))
    else:
        return 'Login Failed'

@app.route('/', methods=['GET'])
def index():
    return 'Welcome to the Index Page!'

@app.route('/user/<user>', methods=['GET'])
def user_page(user):
    return f'Hello, {user}! Welcome to your page.'

@app.route('/admin', methods=['GET'])
def admin_page():
    return 'Welcome to the Admin Page!'