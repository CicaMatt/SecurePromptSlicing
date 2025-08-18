from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="{{ url_for('login') }}">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/session')
def session():
    return '<h2>Welcome to your session page!</h2>'

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            return redirect(url_for('session'))
        else:
            error = 'Invalid username or password'
    return render_template_string(HTML_TEMPLATE, error=error)

if __name__ == '__main__':
    app.run(debug=True)