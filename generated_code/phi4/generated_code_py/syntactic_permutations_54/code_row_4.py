from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML templates as strings for simplicity
login_form_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/do_login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

admin_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Admin Page</title>
  </head>
  <body>
    <h2>Welcome, Admin!</h2>
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

    # Example check for admin credentials
    if username == 'admin' and password == 'password':
        return redirect('/admin_page')
    
    return "Access Denied"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)