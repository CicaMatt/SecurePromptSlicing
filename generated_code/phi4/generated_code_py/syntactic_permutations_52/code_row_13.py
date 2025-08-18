from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

USERNAME = 'admin'
PASSWORD = 'password'

LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form action="" method="post">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
<a href="/secret">Go to Secret Page (no login)</a>
"""

SECRET_PAGE_TEMPLATE = """
<!doctype html>
<title>Secret Page</title>
<h1>Secret settings</h1>
<a href="{{ url_for('login') }}">Back to Login</a>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if username == USERNAME and password == PASSWORD:
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials", 401
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/secret')
def secret():
    return render_template_string(SECRET_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)