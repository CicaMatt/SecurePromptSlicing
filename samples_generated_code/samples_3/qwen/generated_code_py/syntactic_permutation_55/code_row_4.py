from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('<form method="post" action="/do_login">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return f'Logged in as {username}'
    else:
        return 'Invalid credentials'

@app.route('/', methods=['GET'])
def index():
    return 'Welcome to the Index Page!'

@app.route('/user_page', methods=['GET'])
def user_page():
    return 'User Page Content'

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return 'Admin Page Content'

if __name__ == '__main__':
    app.run(debug=True)