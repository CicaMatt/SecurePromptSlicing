from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database of users
users_db = {
    "admin": "password123"
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
    <form method="post" action="/">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
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
            return redirect('/')
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return "Welcome to your Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)