from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple HTML templates as strings
index_html = """
<!doctype html>
<html lang="en">
  <head><title>Index</title></head>
  <body>
    <h1>Welcome to the Index Page</h1>
    <a href="/login">Login</a>
  </body>
</html>
"""

login_html = """
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h1>Login</h1>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

secret_html = """
<!doctype html>
<html lang="en">
  <head><title>Secret Page</title></head>
  <body>
    <h1>Secret settings</h1>
    <p>Welcome, {{ username }}!</p>
    <a href="/">Go back to Index</a>
  </body>
</html>
"""

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "admin"
VALID_PASSWORD = "password"

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials", 401
    return render_template_string(login_html)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    return render_template_string(secret_html, username=session['username'])

if __name__ == '__main__':
    app.run(debug=True)