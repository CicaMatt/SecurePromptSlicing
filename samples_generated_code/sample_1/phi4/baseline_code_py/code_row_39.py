from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == "admin" and password == "password":
        return redirect(url_for('admin_page'))
    elif username == "user" and password == "password":
        return redirect(url_for('user_page'))
    else:
        return "Login Failed"

@app.route('/')
def index():
    return "Index Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/admin')
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)