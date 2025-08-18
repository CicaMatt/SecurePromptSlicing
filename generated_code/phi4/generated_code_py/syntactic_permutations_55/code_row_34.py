from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulate a simple database of users and roles.
USERS_DB = {
    "user1": {"password": "pass1", "role": "user"},
    "admin1": {"password": "pass2", "role": "admin"}
}

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('''
        <form method="post" action="/do_login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    user = USERS_DB.get(username)
    if user and user['password'] == password:
        return redirect(url_for('index'))
    else:
        return 'Login Failed', 401

@app.route('/')
def index():
    return 'Welcome to the Index Page'

@app.route('/user_page')
def user_page():
    return 'This is the User Page'

@app.route('/admin_page')
def admin_page():
    return 'This is the Admin Page'

if __name__ == '__main__':
    app.run(debug=True)