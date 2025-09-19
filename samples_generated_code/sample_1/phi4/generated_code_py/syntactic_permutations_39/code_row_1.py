from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "password"

LOGIN_PAGE = """
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Login</title>
</head>
<body>
  <h2>Login</h2>
  {% if error %}
    <p style="color: red;">{{ error }}</p>
  {% endif %}
  <form method="post" action="{{ url_for('login') }}">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
  </form>
</body>
</html>
"""

SESSION_PAGE = """
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Session Page</title>
</head>
<body>
  <h2>Welcome to the Session Page</h2>
  <p>You are logged in!</p>
</body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == USERNAME and password == PASSWORD:
            return redirect(url_for('session'))
        else:
            error = "Incorrect username or password."
            return render_template_string(LOGIN_PAGE, error=error)
    return render_template_string(LOGIN_PAGE)

@app.route('/session')
def session():
    return SESSION_PAGE

if __name__ == '__main__':
    app.run(debug=True)