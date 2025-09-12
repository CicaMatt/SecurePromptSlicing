from flask import Flask, request, redirect, url_for, render_template_string

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
    
    # Dummy authentication logic
    if username == "admin" and password == "secret":
        return redirect(url_for('admin_page'))
    elif username == "user" and password == "pass":
        return redirect(url_for('user_page'))
    else:
        return 'Login Failed', 401

@app.route('/')
def index():
    return '''
        <h1>Welcome to the Home Page</h1>
        <a href="/login">Login here</a>
    '''

@app.route('/user_page')
def user_page():
    return '<h1>This is the User Page</h1>'

@app.route('/admin_page')
def admin_page():
    return '<h1>This is the Admin Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)