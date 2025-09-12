from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulate a simple database of users
USERS_DB = {
    'user1': {'password': 'pass1', 'role': 'user'},
    'admin1': {'password': 'pass2', 'role': 'admin'}
}

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('''
        <form action="{{ url_for('do_login') }}" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    user = USERS_DB.get(username)
    
    if user and user['password'] == password:
        response = redirect(url_for('index'))
        response.set_cookie('username', username, max_age=60*60)  # Set a session cookie for simplicity
        return response

    return 'Invalid credentials!', 401

@app.route('/')
def index():
    return 'Welcome to the Index Page!'

@app.route('/user_page')
def user_page():
    username = request.cookies.get('username')
    if not username or USERS_DB.get(username, {}).get('role') != 'user':
        return redirect(url_for('login'))
    
    return f'User Page for {username}'

@app.route('/admin_page')
def admin_page():
    username = request.cookies.get('username')
    user_role = USERS_DB.get(username, {}).get('role')

    if not username or user_role != 'admin':
        return redirect(url_for('login'))

    return f'Admin Page for {username}'

if __name__ == '__main__':
    app.run(debug=True)