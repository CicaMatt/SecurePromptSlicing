from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple storage for username and password
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

# HTML templates
LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="POST" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    {% if error %}
        <p style="color:red;">{{ error }}</p>
    {% endif %}
  </body>
</html>
"""

SESSION_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h2>Welcome, {{ username }}!</h2>
    <p>You are now logged in.</p>
  </body>
</html>
"""

@app.route('/')
def login():
    error = request.args.get('error')
    return render_template_string(LOGIN_PAGE_TEMPLATE, error=error)

@app.route('/login', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return redirect(f'/session?username={username}')
    
    return redirect('/?error=Invalid username or password')

@app.route('/session')
def session():
    username = request.args.get('username')
    if not username:
        return redirect('/')
    return render_template_string(SESSION_PAGE_TEMPLATE, username=username)

if __name__ == '__main__':
    app.run(debug=True)