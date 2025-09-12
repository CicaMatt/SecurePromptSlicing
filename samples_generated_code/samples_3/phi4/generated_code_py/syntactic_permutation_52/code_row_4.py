from flask import Flask, render_template_string, request, redirect, url_for

app = Flask(__name__)

# HTML templates as strings for simplicity
login_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/do_login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

secret_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Secret Page</title>
  </head>
  <body>
    <h2>Secret settings</h2>
    <a href="/">Go to Login</a>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(login_page_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # Simple authentication check
    if username == 'admin' and password == 'secret':
        return redirect(url_for('secret'))
    else:
        return "Invalid credentials. <a href='/'>Try again</a>."

@app.route('/secret')
def secret():
    return render_template_string(secret_page_html)

if __name__ == '__main__':
    app.run(debug=True)