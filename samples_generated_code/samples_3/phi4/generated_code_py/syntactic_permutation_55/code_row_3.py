from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return jsonify({'status': 'success', 'message': 'Logged in successfully'})
    else:
        return jsonify({'status': 'failure', 'message': 'Invalid credentials'})

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