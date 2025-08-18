from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users
users_db = {
    "admin": "password123"
}

login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
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
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return render_template_string(dashboard_html)
    return render_template_string(login_page_html)

if __name__ == '__main__':
    app.run(debug=True)