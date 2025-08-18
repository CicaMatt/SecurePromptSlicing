from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    'user': {'password': 'password123', 'role': 'user'},
    'admin': {'password': 'adminpass', 'role': 'admin'}
}

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
    username = request.form.get('username')
    password = request.form.get('password')

    if username in users_db and users_db[username]['password'] == password:
        return redirect(url_for('user_page' if users_db[username]['role'] == 'user' else 'admin_page'))
    
    return "Invalid credentials", 401

@app.route('/logout', methods=['GET'])
def logout():
    # Implement session termination logic here
    return redirect(url_for('login'))

@app.route('/user_page', methods=['GET'])
def user_page():
    return "<h1>Welcome to the User Page</h1>"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "<h1>Welcome to the Admin Page</h1>"

if __name__ == '__main__':
    app.run(debug=True)