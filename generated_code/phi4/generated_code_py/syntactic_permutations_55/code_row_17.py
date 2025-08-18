from flask import Flask, request, redirect, url_for

app = Flask(__name__)

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
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'secret':
        return redirect(url_for('admin_page'))
    elif username == 'user' and password == 'pass':
        return redirect(url_for('user_page'))
    else:
        return "Invalid credentials"

@app.route('/')
def index():
    return "Welcome to the Index Page!"

@app.route('/user')
def user_page():
    return "This is the User's Page."

@app.route('/admin')
def admin_page():
    return "Welcome to the Admin Page."

if __name__ == '__main__':
    app.run(debug=True)