from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = "admin"
PASSWORD = "secret"

login_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
  </head>
  <body>
    <h2>Login</h2>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="{{ url_for('login') }}">
      Username:<br>
      <input type="text" name="username"><br>
      Password:<br>
      <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username != USERNAME or password != PASSWORD:
            error = 'Invalid username or password'
        else:
            return redirect(url_for('session'))
    return render_template_string(login_form, error=error)

@app.route('/session')
def session():
    return '<h2>Welcome to your session page!</h2>'

if __name__ == '__main__':
    app.run(debug=True)