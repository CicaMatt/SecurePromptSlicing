from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML template for login form
LOGIN_FORM_HTML = """
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form> 
  </body>
</html>
"""

# HTML template for admin page
ADMIN_PAGE_HTML = """
<!doctype html>
<html lang="en">
  <head>
    <title>Admin Page</title>
  </head>
  <body>
    <h2>Welcome to the Admin Page!</h2>
  </body>
</html>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM_HTML)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Simple admin check (for demonstration purposes)
    if username == 'admin' and password == 'password':  # Replace with real validation logic
        return redirect('/admin_page')
    
    return "Login Failed"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(ADMIN_PAGE_HTML)

if __name__ == '__main__':
    app.run(debug=True)