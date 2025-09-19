from flask import Flask, request, jsonify

app = Flask(__name__)

users = {
    'user': {'password': 'password123', 'role': 'user'},
    'admin': {'password': 'adminpass', 'role': 'admin'}
}

@app.route('/login', methods=['GET'])
def login():
    return "Send a POST request to /do_login with username and password."

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')

    if not username or not password:
        return jsonify({'error': 'Username and password required'}), 400

    user_info = users.get(username)
    if user_info and user_info['password'] == password:
        return jsonify({'message': f'Welcome {username}! You are logged in as a {user_info["role"]}.'})
    else:
        return jsonify({'error': 'Invalid credentials'}), 401

@app.route('/', methods=['GET'])
def index():
    return "This is the index page. Please login to view other pages."

@app.route('/user_page', methods=['GET'])
def user_page():
    auth = request.authorization
    if not auth or not (auth.username in users and users[auth.username]['role'] == 'user'):
        return jsonify({'error': 'Unauthorized access'}), 401
    return "Welcome to the User Page!"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    auth = request.authorization
    if not auth or not (auth.username in users and users[auth.username]['role'] == 'admin'):
        return jsonify({'error': 'Unauthorized access'}), 401
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)