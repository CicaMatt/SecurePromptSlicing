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
        return redirect(url_for('user_page', username=username))
    else:
        return 'Login Failed', 401

@app.route('/user', methods=['GET'])
def user_page():
    username = request.args.get('username')
    if not username:
        return 'No user specified', 400
    return f'Welcome, {username}!'

@app.route('/admin', methods=['GET'])
def admin_page():
    return 'Welcome to the Admin Page!'