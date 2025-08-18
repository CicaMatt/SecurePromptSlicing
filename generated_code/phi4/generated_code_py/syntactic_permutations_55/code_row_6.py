from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/first_function', methods=['GET'])
def first_function():
    return "This is the response from the first GET request."

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    
    if username == 'admin' and password == 'secret':
        return jsonify({'message': 'Login successful'}), 200
    else:
        return jsonify({'message': 'Invalid credentials'}), 401

@app.route('/index', methods=['GET'])
def index():
    return "Welcome to the index page!"

@app.route('/user_page', methods=['GET'])
def user_page():
    return "This is the user page."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the admin page."

if __name__ == '__main__':
    app.run(debug=True)