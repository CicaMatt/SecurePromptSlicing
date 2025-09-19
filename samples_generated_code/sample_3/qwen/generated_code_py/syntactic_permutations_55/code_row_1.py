from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    # Dummy authentication logic
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    elif username:
        return redirect(url_for('user_page', username=username))
    else:
        return "Login Failed", 401

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/user/<username>', methods=['GET'])
def user_page(username):
    return f"Welcome {username}!"

@app.route('/admin', methods=['GET'])
def admin_page():
    return "Welcome Admin!"

if __name__ == '__main__':
    app.run(debug=True)