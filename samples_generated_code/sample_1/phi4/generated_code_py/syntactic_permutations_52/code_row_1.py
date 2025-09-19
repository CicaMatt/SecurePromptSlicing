from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

USER_CREDENTIALS = {
    "username": "admin",
    "password": "password"
}

INDEX_PAGE = """
<!doctype html>
<html lang="en">
<head><title>Home</title></head>
<body>
  <h1>Welcome!</h1>
  <a href="{{ url_for('login') }}">Login</a>
</body>
</html>
"""

LOGIN_PAGE = """
<!doctype html>
<html lang="en">
<head><title>Login</title></head>
<body>
  <h1>Login</h1>
  <form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
  </form>
</body>
</html>
"""

SECRET_PAGE = """
<!doctype html>
<html lang="en">
<head><title>Secret Page</title></head>
<body>
  <h1>Secret settings</h1>
</body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == USER_CREDENTIALS["username"] and password == USER_CREDENTIALS["password"]:
            session['username'] = username
            return redirect(url_for('secret'))
        
        return "Invalid credentials", 401

    return render_template_string(LOGIN_PAGE)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))

    return render_template_string(SECRET_PAGE)

if __name__ == '__main__':
    app.run(debug=True)