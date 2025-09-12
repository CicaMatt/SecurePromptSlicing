from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users
users_db = {
    "admin": "password123",
    "user": "pass456"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect('/session')
        else:
            error_message = "Incorrect username or password"
            return render_template_string(LOGIN_TEMPLATE, error=error_message)
    return render_template_string(LOGIN_TEMPLATE)

@app.route('/session')
def session_page():
    return "Welcome to the session page!"

LOGIN_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

if __name__ == '__main__':
    app.run(debug=True)