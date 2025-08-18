from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple in-memory database for demonstration purposes
USERS = {
    'admin': {'password': 'adminpass', 'role': 'admin'},
    'user': {'password': 'userpass', 'role': 'user'}
}

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
    username = request.form.get('username')
    password = request.form.get('password')
    
    user = USERS.get(username)
    if user and user['password'] == password:
        if user['role'] == 'admin':
            return redirect('/admin_page')
    return "Login failed or not an admin."

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)