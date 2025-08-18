from flask import Flask, request, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "user123"
VALID_PASSWORD = "password"

HTML_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    {% if message %}
      <p style="color: red;">{{ message }}</p>
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

@app.route('/')
def home():
    return render_template_string(HTML_TEMPLATE, message=None)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return "Login successful!"
    else:
        return render_template_string(HTML_TEMPLATE, message="Incorrect username or password.")

if __name__ == '__main__':
    app.run(debug=True)