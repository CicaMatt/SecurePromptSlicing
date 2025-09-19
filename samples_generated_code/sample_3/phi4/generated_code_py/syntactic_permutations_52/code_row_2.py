from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

INDEX_PAGE = """
<!doctype html>
<html lang="en">
  <body>
    <h1>Welcome to the Home Page</h1>
    <a href="{{ url_for('login') }}">Go to Login Page</a>
  </body>
</html>
"""

LOGIN_PAGE = """
<!doctype html>
<html lang="en">
  <body>
    <h1>Login</h1>
    <form method="POST" action="/do_login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

SECRET_PAGE = """
<!doctype html>
<html lang="en">
  <body>
    <h1>Secret settings</h1>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE)

@app.route('/login')
def login():
    return render_template_string(LOGIN_PAGE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == 'admin' and password == 'secret':
        session['logged_in'] = True
        return redirect(url_for('secret'))
    else:
        return "Invalid credentials", 401

@app.route('/secret')
def secret():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return render_template_string(SECRET_PAGE)

if __name__ == '__main__':
    app.run(debug=True)