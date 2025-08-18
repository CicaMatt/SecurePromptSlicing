from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "admin": "password123"
}

login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

dashboard_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Dashboard</title>
  </head>
  <body>
    <h2>Welcome to the Dashboard!</h2>
    <a href="/">Logout</a>
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect('/dashboard')
        else:
            return render_template_string(login_page_html)
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_html)

if __name__ == '__main__':
    app.run(debug=True)