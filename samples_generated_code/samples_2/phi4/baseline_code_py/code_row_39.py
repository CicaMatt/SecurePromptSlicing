from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML template for login form
login_form_html = """
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/do_login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form> 
  </body>
</html>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # Dummy check for admin credentials
    if username == 'admin' and password == 'secret':
        return redirect('/admin_page')
    
    return "Login failed. Not an admin."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "<h1>Welcome to the Admin Page</h1>"

if __name__ == '__main__':
    app.run(debug=True)