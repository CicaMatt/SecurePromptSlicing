from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for simplicity; in a real application use a secure method.
CORRECT_USERNAME = "admin"
CORRECT_PASSWORD = "password"

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
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
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
    <h2>Welcome to the Session Page!</h2>
    <p>You are logged in.</p>
  </body>
</html>
"""

@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == CORRECT_USERNAME and password == CORRECT_PASSWORD:
            return render_template_string(SESSION_PAGE_TEMPLATE)
        else:
            error_message = "Invalid username or password."
            return render_template_string(LOGIN_PAGE_TEMPLATE, error=error_message)

    return render_template_string(LOGIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)