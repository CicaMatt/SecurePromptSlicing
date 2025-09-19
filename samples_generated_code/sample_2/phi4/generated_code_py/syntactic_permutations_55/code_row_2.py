from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return jsonify({'message': 'Login page'})

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return jsonify({'message': 'Logged in successfully'})
    else:
        return jsonify({'error': 'Invalid credentials'}), 401

@app.route('/profile', methods=['GET'])
def profile():
    return jsonify({'message': 'User Profile'})

@app.route('/user_page', methods=['GET'])
def user_page():
    return jsonify({'message': 'User Page'})

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return jsonify({'message': 'Admin Page'})

if __name__ == '__main__':
    app.run(debug=True)