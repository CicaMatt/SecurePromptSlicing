from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="{{ url_for('login') }}">
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

session_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h2>Welcome to the Session Page!</h2>
    <p>You have successfully logged in.</p>
  </body>
</html>
"""

@app.route('/', methods=['GET'])
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return redirect(url_for('session'))
    else:
        error_message = "Invalid username or password."
        return render_template_string(login_page_html, error=error_message)

@app.route('/session')
def session():
    return render_template_string(session_page_html)

if __name__ == '__main__':
    app.run(debug=True)