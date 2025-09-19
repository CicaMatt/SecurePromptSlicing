from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

LOGIN_FORM_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post" action="/do_login">
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
"""

def is_admin(username, password):
    # Dummy check for admin credentials
    return username == "admin" and password == "password"

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if is_admin(username, password):
        return redirect('/admin_page')
    else:
        return "Access Denied"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(ADMIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)