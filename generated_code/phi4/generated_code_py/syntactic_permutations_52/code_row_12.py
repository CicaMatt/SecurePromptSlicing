from flask import Flask, request, render_template_string

app = Flask(__name__)

login_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/do_login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/')
def login():
    return render_template_string(login_page_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'secret':
        return "<h1>Secret settings</h1>"
    else:
        return "Invalid credentials"

if __name__ == '__main__':
    app.run(debug=True)