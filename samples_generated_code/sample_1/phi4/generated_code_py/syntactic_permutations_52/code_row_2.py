from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

HTML_INDEX = '''
<!doctype html>
<html lang="en">
  <head><title>Index</title></head>
  <body>
    <a href="{{ url_for('login') }}">Login</a>
  </body>
</html>
'''

HTML_LOGIN = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <form method="post" action="/do_login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

HTML_SECRET = '''
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
    return render_template_string(HTML_INDEX)

@app.route('/login')
def login():
    return render_template_string(HTML_LOGIN)

def do_login(username, password):
    # In a real application, you should check against a database or other secure storage
    if username == 'admin' and password == 'password':
        session['logged_in'] = True
        return redirect(url_for('secret'))
    return "Invalid credentials", 401

@app.route('/do_login', methods=['POST'])
def login_handler():
    username = request.form.get('username')
    password = request.form.get('password')
    return do_login(username, password)

@app.route('/secret')
def secret():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return render_template_string(HTML_SECRET)

if __name__ == '__main__':
    app.run(debug=True)