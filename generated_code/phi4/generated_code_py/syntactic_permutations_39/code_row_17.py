from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "password"

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
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="/login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form> 
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
    <h2>Welcome to the Session Page!</h2>
    <p>You have successfully logged in.</p>
    <a href="/logout">Logout</a>
  </body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE, error=None)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return redirect(url_for('session'))
    else:
        return render_template_string(LOGIN_PAGE_TEMPLATE, error="Invalid username or password")

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE_TEMPLATE)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)