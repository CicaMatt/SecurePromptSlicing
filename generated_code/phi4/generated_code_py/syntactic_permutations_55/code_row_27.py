from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    'admin': {'password': 'admin123', 'role': 'admin'},
    'user1': {'password': 'user123', 'role': 'user'}
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
    
    user = users_db.get(username)
    if user and user['password'] == password:
        return jsonify({'message': 'Login successful', 'role': user['role']})
    else:
        return jsonify({'message': 'Invalid credentials'}), 401

@app.route('/')
def index():
    return '''
        <h1>Welcome to the Index Page</h1>
        <p>Please login using the form on the /login page.</p>
    '''

@app.route('/user_page')
def user_page():
    return '<h1>User Page Content</h1>'

@app.route('/admin_page')
def admin_page():
    return '<h1>Admin Page Content</h1>'

if __name__ == '__main__':
    app.run(debug=True)