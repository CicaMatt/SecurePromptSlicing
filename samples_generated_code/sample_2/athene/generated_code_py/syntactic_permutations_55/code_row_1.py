from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('<form method="post" action="/do_login">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return '<h1>Welcome Admin</h1>'
    else:
        return '<h1>Login Failed</h1>'

@app.route('/', methods=['GET'])
def index():
    return '<h1>Welcome to the Index Page</h1>'

@app.route('/user', methods=['GET'])
def user_page():
    return '<h1>User Page</h1>'

@app.route('/admin', methods=['GET'])
def admin_page():
    return '<h1>Admin Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)