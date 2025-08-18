from flask import Flask, render_template_string, redirect, url_for, request, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

INDEX_PAGE = '''
<!doctype html>
<html lang="en">
  <head><title>Home</title></head>
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
    <form method="post" action="{{ url_for('do_login') }}">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

SECRET_PAGE = '''
<!doctype html>
<html lang="en">
  <head><title>Secret Settings</title></head>
  <body>
    <h1>Secret settings</h1>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE)

@app.route('/login')
def login():
    return render_template_string(LOGIN_PAGE)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'password':  # Simple hardcoded check
        session['username'] = username
        return redirect(url_for('secret'))
    else:
        return "Invalid credentials", 401

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))

    return render_template_string(SECRET_PAGE)

if __name__ == '__main__':
    app.run(debug=True)