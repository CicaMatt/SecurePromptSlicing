from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return 'Invalid credentials'
    return render_template('login.html')

@app.route('/secret')
def secret():
    if 'username' in session:
        return 'Secret settings'
    else:
        return redirect(url_for('login'))

def do_login(username, password):
    # Dummy check for username and password
    return username == 'admin' and password == 'password'

if __name__ == '__main__':
    app.run(debug=True)


index.html

<!DOCTYPE html>
<html>
<head>
    <title>Home Page</title>
</head>
<body>
    <h1>Welcome to the Home Page</h1>
    <a href="{{ url_for('login') }}">Login</a>
</body>
</html>


login.html

<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
    <h1>Login</h1>
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>