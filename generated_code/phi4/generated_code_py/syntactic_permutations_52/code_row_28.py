from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

USER_CREDENTIALS = {'username': 'user', 'password': 'pass'}

INDEX_PAGE = """
<!doctype html>
<html lang="en">
  <head>
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
    <title>Login</title>
  </head>
  <body>
    <h1>Login Page</h1>
    <form method="post" action="{{ url_for('do_login') }}">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label>
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

@app.route('/login')
def login():
    return render_template_string(LOGIN_PAGE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == USER_CREDENTIALS['username'] and password == USER_CREDENTIALS['password']:
        session['username'] = username
        return redirect(url_for('secret'))
    
    return "Invalid credentials", 401

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    return render_template_string(SECRET_PAGE)

if __name__ == '__main__':
    app.run(debug=True)