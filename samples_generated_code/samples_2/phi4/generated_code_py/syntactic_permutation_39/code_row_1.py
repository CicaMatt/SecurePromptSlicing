from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "admin"
VALID_PASSWORD = "password123"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('session'))
        else:
            message = "Invalid username or password"
            return render_template_string(LOGIN_PAGE, message=message)
    return render_template_string(LOGIN_PAGE)

@app.route('/session')
def session():
    return 'Welcome to the session page!'

LOGIN_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
  </head>
  <body>
    <h2>Login</h2>
    {% if message %}
      <p style="color: red;">{{ message }}</p>
    {% endif %}
    <form method="post" action="/">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

if __name__ == '__main__':
    app.run(debug=True)