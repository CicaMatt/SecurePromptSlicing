from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = 'user'
VALID_PASSWORD = 'pass'

LOGIN_PAGE_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
    {% if error %}
        <p style="color:red;">{{ error }}</p>
    {% endif %}
  </body>
</html>
'''

SESSION_PAGE_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h2>Welcome to the Session Page!</h2>
    <p>You have successfully logged in.</p>
    <a href="/">Logout</a>
  </body>
</html>
'''

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE, error=None)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return redirect(url_for('session'))
    
    return render_template_string(LOGIN_PAGE_TEMPLATE, error="Invalid username or password.")

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)