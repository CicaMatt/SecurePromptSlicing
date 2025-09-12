from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Simple in-memory storage for demonstration purposes
users = {
    'admin': 'password123'
}

login_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    <form action="/do_login" method="post">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form> 
  </body>
</html>
'''

admin_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Admin Page</title>
  </head>
  <body>
    <h1>Welcome to the Admin Page</h1>
  </body>
</html>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if users.get(username) == password and username == 'admin':
        return redirect('/admin_page')
    else:
        return "Login failed"

@app.route('/admin_page')
def admin_page_view():
    return render_template_string(admin_page)

if __name__ == '__main__':
    app.run(debug=True)