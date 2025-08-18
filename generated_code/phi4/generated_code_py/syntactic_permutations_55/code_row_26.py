from flask import Flask, request, jsonify

app = Flask(__name__)

users = {
    "admin": {"password": "adminpass", "role": "admin"},
    "user1": {"password": "user1pass", "role": "user"}
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

    if username in users and users[username]['password'] == password:
        response = {'status': 'success', 'role': users[username]['role']}
    else:
        response = {'status': 'failure'}

    return jsonify(response)

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Home Page!"

@app.route('/user_page', methods=['GET'])
def user_page():
    auth = request.authorization
    if not auth or (auth.username != "admin" and auth.password != "adminpass"):
        return "Unauthorized", 401

    return "This is the User Page."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    auth = request.authorization
    if not auth or (auth.username != "admin" or users.get(auth.username, {}).get('role') != 'admin'):
        return "Unauthorized", 401

    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)