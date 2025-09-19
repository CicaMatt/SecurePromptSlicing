from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

INDEX_PAGE = '''
<!doctype html>
<html>
    <body>
        <h1>Welcome to the Home Page</h1>
        <a href="{{ url_for('login') }}">Login</a>
    </body>
</html>
'''

LOGIN_PAGE = '''
<!doctype html>
<html>
    <body>
        <h1>Login Page</h1>
        <form method="POST">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    </body>
</html>
'''

SECRET_PAGE = '''
<!doctype html>
<html>
    <body>
        <h1>Secret Settings</h1>
    </body>
</html>
'''

def do_login(username, password):
    # Dummy check for username and password
    return username == 'admin' and password == 'password'

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials", 401

    return render_template_string(LOGIN_PAGE)

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(SECRET_PAGE)
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)