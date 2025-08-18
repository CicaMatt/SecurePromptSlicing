from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    # Here you would have logic to verify the user credentials
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    elif username == 'user' and password == 'user':
        return redirect(url_for('user_page'))
    else:
        return "Invalid Credentials", 401

@app.route('/')
def index():
    return "Home Page"

@app.route('/user_page', methods=['GET'])
def user_page():
    return "User Page Content"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Admin Page Content"

if __name__ == '__main__':
    app.run(debug=True)