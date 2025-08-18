from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = "admin"
PASSWORD = "password"

login_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="/">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password"><br><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == USERNAME and password == PASSWORD:
            return redirect('/session')
        else:
            error = "Invalid username or password"
    return render_template_string(login_html, error=error)

@app.route('/session')
def session():
    return "<h1>Welcome to your session!</h1>"

if __name__ == '__main__':
    app.run(debug=True)