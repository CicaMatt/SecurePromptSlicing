from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    # Logic for verifying credentials and handling login
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    elif username != '' and password != '':
        return redirect(url_for('user_page', username=username))
    else:
        return "Invalid Credentials"

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Home Page!"

@app.route('/user/<username>', methods=['GET'])
def user_page(username):
    return f"User Page for {username}"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)