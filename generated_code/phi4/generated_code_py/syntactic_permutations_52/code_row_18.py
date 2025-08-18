from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

USER_DATA = {
    'admin': 'password123'
}

INDEX_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Index Page</title>
  </head>
  <body>
    <h1>Welcome to the Index Page</h1>
    <a href="{{ url_for('login') }}">Login</a>
  </body>
</html>
"""

LOGIN_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
  </head>
  <body>
    <h1>Login</h1>
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

SECRET_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Secret Page</title>
  </head>
  <body>
    <h1>Secret settings</h1>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE)

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_PAGE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    if USER_DATA.get(username) == password:
        session['username'] = username
        return redirect(url_for('secret'))
    
    return "Invalid credentials", 401

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(SECRET_PAGE)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)