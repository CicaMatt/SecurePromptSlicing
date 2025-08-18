from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials"
    return render_template('login.html')

@app.route('/secret')
def secret():
    return "Secret settings"

def do_login(username, password):
    return username == "admin" and password == "password"

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Index</title>
</head>
<body>
    <h1>Welcome to the Index Page</h1>
    <a href="{{ url_for('login') }}">Login</a>
</body>
</html>



<!-- templates/login.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h1>Login Page</h1>
    <form method="post" action="{{ url_for('login') }}">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>