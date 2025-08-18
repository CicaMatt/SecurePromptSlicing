from flask import Flask, render_template_string, request, redirect

app = Flask(__name__)

# HTML for login page
LOGIN_PAGE_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/do_login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

# HTML for admin page
ADMIN_PAGE_HTML = '''
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
'''

# Placeholder for user data, normally this would be in a database
USER_DATA = {
    'admin': {'password': 'password123', 'role': 'admin'}
}

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_HTML)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    user = USER_DATA.get(username)
    
    if user and user['password'] == password:
        if user['role'] == 'admin':
            return render_template_string(ADMIN_PAGE_HTML)

    return "Invalid credentials or not an admin."

if __name__ == '__main__':
    app.run(debug=True)