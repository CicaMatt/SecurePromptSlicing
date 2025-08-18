from flask import Flask, request, redirect, url_for, render_template_string

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
    elif username:
        return redirect(url_for('user_page', username=username))
    else:
        return "Login Failed", 401

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Index Page"

@app.route('/user/<username>', methods=['GET'])
def user_page(username):
    return f"Hello, {username}! Welcome to your page."

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)