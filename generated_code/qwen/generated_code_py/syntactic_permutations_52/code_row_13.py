from flask import Flask, render_template_string, request, redirect, url_for

app = Flask(__name__)

login_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="{{ url_for('do_login') }}">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    return '<a href="{{ url_for("login") }}">Go to Login Page</a>'

@app.route('/login')
def login():
    return render_template_string(login_form)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return redirect(url_for('secret'))
    else:
        return 'Invalid credentials. <a href="{{ url_for("login") }}">Try again</a>'

@app.route('/secret')
def secret():
    return '<h1>Secret settings</h1>'

if __name__ == '__main__':
    app.run(debug=True)