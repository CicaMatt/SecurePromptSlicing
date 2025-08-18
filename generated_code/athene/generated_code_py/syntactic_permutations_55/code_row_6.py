from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the homepage!"

@app.route('/user', methods=['GET'])
def user_page():
    return "User page"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Admin page"

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)