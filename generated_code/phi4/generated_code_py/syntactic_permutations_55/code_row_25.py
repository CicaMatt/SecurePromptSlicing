from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page: Please enter your credentials."

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return jsonify({'status': 'success', 'message': 'Login successful!'})
    else:
        return jsonify({'status': 'failure', 'message': 'Invalid credentials!'})

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the home page!"

@app.route('/about', methods=['GET'])
def about():
    return "This is the about page."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page. You must be logged in as an administrator to view this."

if __name__ == '__main__':
    app.run(debug=True)