from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/do_login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
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
    <h2>Welcome Admin!</h2>
    <p>You have access to the admin page.</p>
  </body>
</html>
"""

def is_admin(username, password):
    # For demonstration purposes, using a hardcoded check
    return username == "admin" and password == "password"

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if is_admin(username, password):
        return redirect('/admin_page')
    else:
        return "Login Failed", 401

@app.route('/admin_page')
def admin_page():
    return render_template_string(ADMIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)