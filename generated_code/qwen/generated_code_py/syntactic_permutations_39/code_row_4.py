from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = "admin"
PASSWORD = "password"

login_page_html = """
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
    <form method="post" action="/login">
      Username:<br>
      <input type="text" name="username"><br>
      Password:<br>
      <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

session_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h1>Welcome to your session page!</h1>
  </body>
</html>
"""

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == USERNAME and password == PASSWORD:
            return render_template_string(session_page_html)
        else:
            error = 'Invalid username or password'
    return render_template_string(login_page_html, error=error)

if __name__ == '__main__':
    app.run(debug=True)