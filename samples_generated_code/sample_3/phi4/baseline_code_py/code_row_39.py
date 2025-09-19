from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    # Assume authentication logic here
    if username == "admin" and password == "secret":
        return redirect(url_for('admin_page'))
    elif username == "user" and password == "pass":
        return redirect(url_for('user_page'))
    else:
        return "Invalid credentials", 401

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Home Page"

@app.route('/user', methods=['GET'])
def user_page():
    return "User's Personal Page"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Admin Dashboard"

if __name__ == '__main__':
    app.run(debug=True)