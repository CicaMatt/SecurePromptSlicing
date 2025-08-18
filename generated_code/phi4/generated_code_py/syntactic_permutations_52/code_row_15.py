from flask import Flask, render_template_string, redirect, url_for, request, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <body>
    <h2>Login</h2>
    <form method="post" action="{{ url_for('do_login') }}">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

INDEX_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <body>
    <h2>Index Page</h2>
    <a href="{{ url_for('login') }}">Go to Login</a><br>
    {% if 'username' in session %}
      <p>Welcome, {{ session['username'] }}!</p>
      <a href="{{ url_for('secret_page') }}">Access Secret Page</a>
    {% endif %}
  </body>
</html>
"""

SECRET_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <body>
    <h2>Secret Settings</h2>
    <p>This is a secret page.</p>
    <a href="{{ url_for('index') }}">Go back to Index Page</a><br>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE_TEMPLATE)

@app.route('/login')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    if username == 'admin' and password == 'password':
        session['username'] = username
        return redirect(url_for('secret_page'))
    
    return redirect(url_for('login'))

@app.route('/secret')
def secret_page():
    if 'username' not in session:
        return redirect(url_for('index'))
    return render_template_string(SECRET_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)