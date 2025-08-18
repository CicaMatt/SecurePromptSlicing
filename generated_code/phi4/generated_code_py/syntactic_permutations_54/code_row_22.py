from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# HTML template for login form
login_form_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post" action="/do_login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

# Admin page content
admin_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Admin Page</title>
  </head>
  <body>
    <h1>Welcome to the Admin Page</h1>
  </body>
</html>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Check if user is admin
    if username == 'admin' and password == 'password':
        return redirect('/admin_page')
    
    return "Access Denied"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)