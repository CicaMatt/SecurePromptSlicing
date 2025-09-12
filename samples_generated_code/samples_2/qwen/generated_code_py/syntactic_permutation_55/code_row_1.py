from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('''
        <form action="{{ url_for('do_login') }}" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return redirect(url_for('user_page'))
    else:
        return 'Invalid credentials'

@app.route('/dashboard', methods=['GET'])
def dashboard():
    return 'Welcome to your Dashboard!'

@app.route('/user_page', methods=['GET'])
def user_page():
    return 'Welcome to the User Page!'

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return 'Welcome to the Admin Page!'

if __name__ == '__main__':
    app.run(debug=True)