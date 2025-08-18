from flask import Flask, request, redirect, url_for

app = Flask(__name__)

users = {'user': 'password', 'admin': 'adminpass'}

@app.route('/login', methods=['GET'])
def login():
    return '''
        <h1>Login</h1>
        <form action="/do_login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username in users and users[username] == password:
        return redirect(url_for('index'))
    else:
        return 'Invalid credentials, please try again.'

@app.route('/')
def index():
    return '<h1>Welcome to the Index Page</h1>'

@app.route('/user_page', methods=['GET'])
def user_page():
    username = request.args.get('username')
    if username and username in users:
        return f'<h1>User Page for {username}</h1>'
    else:
        return redirect(url_for('login'))

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return '<h1>Welcome to the Admin Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)