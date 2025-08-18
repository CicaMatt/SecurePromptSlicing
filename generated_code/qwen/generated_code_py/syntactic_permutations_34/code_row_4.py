from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory database simulation
users_db = {
    "user1": "password1",
    "user2": "password2"
}

login_page = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <form method="post" action="/login">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password"><br><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>
"""

dashboard_page = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Dashboard</title>
  </head>
  <body>
    <h1>Welcome to the Dashboard</h1>
  </body>
</html>
"""

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if users_db.get(username) == password:
            return render_template_string(dashboard_page)
        else:
            return redirect('/login')
    return render_template_string(login_page)

if __name__ == '__main__':
    app.run(debug=True)