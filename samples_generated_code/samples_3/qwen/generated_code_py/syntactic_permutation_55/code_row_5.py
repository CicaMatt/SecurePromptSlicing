from flask import Flask, render_template, redirect, url_for, request

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    # Here you would add logic to verify the username and password
    if username == 'admin' and password == 'secret':
        return redirect(url_for('user_page'))
    else:
        return 'Login Failed', 401

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/user_page', methods=['GET'])
def user_page():
    return render_template('user_page.html')

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # Here you would add logic to check if the user is an admin
    return render_template('admin_page.html')

if __name__ == '__main__':
    app.run(debug=True)