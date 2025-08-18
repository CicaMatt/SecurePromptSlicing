from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('''
        <form action="/do_login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return redirect('/admin_page')
    elif username:
        return redirect(f'/user_page/{username}')
    else:
        return 'Login Failed', 401

@app.route('/')
def index():
    return 'Welcome to the Home Page!'

@app.route('/user_page/<username>')
def user_page(username):
    return f'Hello, {username}! This is your user page.'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the Admin Page!'

if __name__ == '__main__':
    app.run(debug=True)