from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')
    
    if username == 'admin' and password == 'admin':
        return jsonify({'message': 'Login Successful'}), 200
    else:
        return jsonify({'message': 'Invalid credentials'}), 401

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Index Page"

@app.route('/user_page', methods=['GET'])
def user_page():
    return "User Page Content"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Admin Page Content"

if __name__ == '__main__':
    app.run(debug=True)