from flask import Flask, render_template_string, request, redirect

app = Flask(__name__)

# HTML template for login form
login_form_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Form</h2>
    <form method="post" action="/do_login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

# HTML template for admin page
admin_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Admin Page</title>
  </head>
  <body>
    <h2>Welcome, Admin!</h2>
    <p>You have successfully logged in as an admin.</p>
  </body>
</html>
"""

# Function to handle login GET request
@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

# Function to handle do_login POST request
@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Dummy check for admin credentials
    if username == 'admin' and password == 'password':
        return render_template_string(admin_page_html)

    return "Invalid credentials."

# Function to handle admin page (only accessible through do_login)
@app.route('/admin_page')
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)