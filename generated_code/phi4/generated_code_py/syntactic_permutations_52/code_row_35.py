from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# HTML templates as strings for simplicity
index_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Index</title>
</head>
<body>
    <h1>Welcome to the Home Page</h1>
    <a href="{{ url_for('login') }}">Login</a>
</body>
</html>
"""

login_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h1>Login Page</h1>
    <form method="POST" action="{{ url_for('do_login') }}">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

secret_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Secret Page</title>
</head>
<body>
    <h1>Secret settings</h1>
</body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login')
def login():
    return render_template_string(login_html)

def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == 'admin' and password == 'secret':
        session['username'] = username
        return redirect(url_for('secret'))
    else:
        return "Invalid credentials", 401

@app.route('/do_login', methods=['POST'])
def do_login_route():
    return do_login()

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    return render_template_string(secret_html)

if __name__ == '__main__':
    app.run(debug=True)