from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "admin"
PASSWORD = "password123"

login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    {% if error %}
      <p style="color: red;">Invalid username or password. Please try again.</p>
    {% endif %}
    <form method="post" action="/login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
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
    <a href="/login">Logout</a>
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
        if username == USERNAME and password == PASSWORD:
            return render_template_string(dashboard_html)
        else:
            return render_template_string(login_page_html, error=True)
    
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return redirect('/login')

if __name__ == '__main__':
    app.run(debug=True)