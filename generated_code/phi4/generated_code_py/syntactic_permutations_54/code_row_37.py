from flask import Flask, request, render_template_string

app = Flask(__name__)

# HTML template for login form
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

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == 'admin' and password == 'admin':
        return "Welcome, Admin!"
    else:
        return "Access Denied."

if __name__ == '__main__':
    app.run(debug=True)