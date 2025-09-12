from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# HTML templates for login and admin page
LOGIN_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form action="/do_login" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
"""

ADMIN_PAGE_TEMPLATE = """
<!doctype html>
<title>Admin Page</title>
<h1>Welcome to the Admin Page!</h1>
<p>You have successfully logged in as an admin.</p>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # For demonstration, hardcoding the check for admin
    if username == 'admin' and password == 'password':
        return redirect('/admin_page')
    
    return "Login failed. Please try again."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(ADMIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)