from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML template for login form
LOGIN_FORM_TEMPLATE = """
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

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Simple check for admin credentials
    if username == 'admin' and password == 'password':
        return redirect('/admin_page')
    
    return "Login failed", 401

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "<h1>Welcome to the Admin Page</h1>"

if __name__ == '__main__':
    app.run(debug=True)