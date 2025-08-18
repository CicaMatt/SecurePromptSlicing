from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
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
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
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
    <h2>Welcome to your Dashboard!</h2>
    <a href="/logout">Logout</a>
  </body>
</html>
"""

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect('/dashboard')
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    # Here you would typically check if the user is logged in
    return render_template_string(dashboard_page)

@app.route('/logout')
def logout():
    # Here you would handle logging out the user
    return redirect('/login')

if __name__ == '__main__':
    app.run(debug=True)