from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "This is the login page."

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    if username == 'admin' and password == 'secret':
        return jsonify({'message': 'Login successful', 'role': 'admin'}), 200
    elif username == 'user' and password == 'pass':
        return jsonify({'message': 'Login successful', 'role': 'user'}), 200
    else:
        return jsonify({'message': 'Invalid credentials'}), 401

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Index Page."

@app.route('/user_page', methods=['GET'])
def user_page():
    return "This is the User Page."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "This is the Admin Page."

if __name__ == '__main__':
    app.run(debug=True)