from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple user data for demonstration purposes
USER_DATA = {
    "username": "admin",
    "password": "secret"
}

LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
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
    <h2>Welcome, you are logged in!</h2>
    <a href="/logout">Logout</a>
  </body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE, error=None)

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == USER_DATA['username'] and password == USER_DATA['password']:
        return redirect(url_for('session'))
    else:
        return render_template_string(LOGIN_PAGE_TEMPLATE, error="Username or Password is incorrect")

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE_TEMPLATE)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)