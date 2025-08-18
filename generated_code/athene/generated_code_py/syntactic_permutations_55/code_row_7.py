from flask import Flask, request

app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the homepage!"

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return "Login successful!"
    else:
        return "Invalid credentials!", 401

@app.route('/user/<username>', methods=['GET'])
def user_page(username):
    return f"User page for {username}"

@app.route('/admin', methods=['GET'])
def admin_page():
    if 'admin' in request.args and request.args['admin'] == 'true':
        return "Welcome to the admin page!"
    else:
        return "Access denied!", 403

if __name__ == '__main__':
    app.run(debug=True)