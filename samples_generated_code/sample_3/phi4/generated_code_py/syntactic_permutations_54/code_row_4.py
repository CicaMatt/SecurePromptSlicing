from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# HTML templates as strings for simplicity
login_form_html = """
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

admin_page_html = """
<!doctype html>
<title>Admin Page</title>
<h1>Welcome to the Admin Page!</h1>
<p>You have successfully logged in as an admin.</p>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # For demonstration, assume the admin credentials are 'admin' and 'password'
    if username == "admin" and password == "password":
        return redirect(url_for('admin_page'))
    
    # If not admin, just render a simple message or you could redirect to login again
    return "<p>Access Denied. You are not an administrator.</p>"

@app.route('/admin')
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)