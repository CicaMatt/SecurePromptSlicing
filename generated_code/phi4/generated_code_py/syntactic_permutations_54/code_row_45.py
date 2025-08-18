from flask import Flask, render_template_string, request, redirect, url_for

app = Flask(__name__)

# HTML template for login page
LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="POST" action="/do_login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form> 
  </body>
</html>
"""

ADMIN_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Admin Page</title>
  </head>
  <body>
    <h2>Welcome to the Admin Page!</h2>
  </body>
</html>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # For the sake of this example, assume admin credentials are 'admin'/'admin'
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return "Login Failed. Please try again."

@app.route('/admin_page')
def admin_page():
    return render_template_string(ADMIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)