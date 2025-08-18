from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

HTML_FORM = '''
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
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

HTML_SESSION = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h2>Welcome! You are logged in.</h2>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(HTML_FORM)

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return redirect(url_for('session'))
    else:
        error_message = "Incorrect username or password."
        return render_template_string(HTML_FORM, error=error_message)

@app.route('/session')
def session():
    return render_template_string(HTML_SESSION)

if __name__ == '__main__':
    app.run(debug=True)