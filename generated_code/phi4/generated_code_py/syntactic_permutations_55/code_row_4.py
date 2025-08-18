from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy data for demonstration purposes
users = {'user1': 'password1', 'admin': 'adminpass'}
current_user = None

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
    global current_user
    username = request.form['username']
    password = request.form['password']

    if username in users and users[username] == password:
        current_user = username
        return redirect(url_for('index'))
    
    return 'Invalid credentials!'

@app.route('/')
def index():
    if not current_user:
        return redirect(url_for('login'))

    return f'Welcome {current_user}! <br> <a href="/user_page">User Page</a> | <a href="/admin_page">Admin Page</a>'

@app.route('/user_page')
def user_page():
    if not current_user or current_user != 'user1':
        return 'Access Denied!'
    
    return f'Welcome to User Page, {current_user}!'

@app.route('/admin_page')
def admin_page():
    if not current_user or current_user != 'admin':
        return 'Access Denied!'

    return f'Welcome to Admin Page, {current_user}!'

if __name__ == '__main__':
    app.run(debug=True)