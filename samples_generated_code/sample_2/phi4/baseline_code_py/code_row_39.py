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

    # Simple authentication check (replace with real logic)
    if username == 'admin' and password == 'secret':
        return redirect(url_for('admin_page'))
    elif username == 'user' and password == 'pass123':
        return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/')
def index():
    return '''
        <h1>Welcome to the Homepage</h1>
        <a href="/login">Login</a>
    '''

@app.route('/user')
def user_page():
    return '<h1>User Page</h1>'

@app.route('/admin')
def admin_page():
    return '<h1>Admin Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)