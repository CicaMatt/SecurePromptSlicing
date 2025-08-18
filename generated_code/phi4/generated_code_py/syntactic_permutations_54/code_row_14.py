from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# HTML template for login page
LOGIN_TEMPLATE = '''
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
'''

# Admin page template
ADMIN_PAGE_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Admin Page</title>
  </head>
  <body>
    <h2>Welcome to the Admin Page</h2>
  </body>
</html>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Dummy check for admin credentials
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    
    return "Invalid Credentials"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(ADMIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)