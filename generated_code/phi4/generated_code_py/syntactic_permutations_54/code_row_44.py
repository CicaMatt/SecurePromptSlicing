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

# HTML template for admin page
ADMIN_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Admin Page</title>
  </head>
  <body>
    <h2>Welcome, Admin!</h2>
    <p>You have access to the admin page.</p>
  </body>
</html>
"""

# Simulated user data
USER_DATA = {
    "admin": {"password": "adminpass", "role": "admin"},
    # Add other users if needed
}

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    user_info = USER_DATA.get(username)
    
    if user_info and user_info['password'] == password:
        if user_info['role'] == 'admin':
            return redirect('/admin_page')
        else:
            return "Login successful, but not an admin."
    
    return "Invalid username or password."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(ADMIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)