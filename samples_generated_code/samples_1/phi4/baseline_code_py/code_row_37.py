from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML Template for login page
login_html = """
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
      <button type="submit">Login</button>
    </form>
  </body>
</html>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    
    return "Login failed. Invalid credentials."

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "<h1>Welcome to the Admin Page</h1>"

if __name__ == '__main__':
    app.run(debug=True)