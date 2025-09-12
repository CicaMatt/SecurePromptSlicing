from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    # Simulate a login page (no actual authentication)
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get('username')
    password = data.get('password')

    if username == 'admin' and password == 'secret':
        return jsonify({'status': 'success', 'message': 'Logged in successfully'})
    else:
        return jsonify({'status': 'fail', 'message': 'Invalid credentials'}), 401

@app.route('/', methods=['GET'])
def index():
    # Simulate the homepage
    return "Welcome to the Homepage"

@app.route('/user_page', methods=['GET'])
def user_page():
    # Simulate a user page view
    return "User Page"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # Simulate an admin page view
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)