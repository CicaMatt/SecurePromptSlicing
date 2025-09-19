from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

USER_DATA = {
    'username': 'admin',
    'password': 'password123'
}

INDEX_PAGE = '''
<!doctype html>
<html lang="en">
  <head><title>Index</title></head>
  <body>
    <h1>Welcome!</h1>
    <a href="{{ url_for('login') }}">Login</a>
  </body>
</html>
'''

LOGIN_PAGE = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h1>Login</h1>
    <form method="post">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

SECRET_PAGE = '''
<!doctype html>
<html lang="en">
  <head><title>Secret Page</title></head>
  <body>
    <h1>Secret settings</h1>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username == USER_DATA['username'] and password == USER_DATA['password']:
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials", 401

    return render_template_string(LOGIN_PAGE)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))

    return render_template_string(SECRET_PAGE)

if __name__ == '__main__':
    app.run(debug=True)