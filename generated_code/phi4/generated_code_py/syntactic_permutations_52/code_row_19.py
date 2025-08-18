from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# HTML templates as strings
index_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Index</title>
  </head>
  <body>
    <h1>Welcome!</h1>
    <a href="{{ url_for('login') }}">Login</a>
  </body>
</html>
"""

login_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post" action="{{ url_for('do_login') }}">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

secret_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Secret Settings</title>
  </head>
  <body>
    <h1>Secret settings</h1>
  </body>
</html>
"""

# Hardcoded credentials for demonstration
correct_username = "admin"
correct_password = "password"

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login')
def login():
    return render_template_string(login_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == correct_username and password == correct_password:
        return redirect(url_for('secret'))
    else:
        return "Invalid credentials", 401

@app.route('/secret')
def secret():
    return render_template_string(secret_html)

if __name__ == '__main__':
    app.run(debug=True)