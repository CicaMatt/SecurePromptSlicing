from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple credentials for demonstration
correct_username = "user"
correct_password = "pass"

# HTML templates as strings
login_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    {% if error %}
      <p style="color:red;">{{ error }}</p>
    {% endif %}
  </body>
</html>
'''

session_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session</title>
  </head>
  <body>
    <h2>Welcome to the Session Page!</h2>
    <a href="{{ url_for('login') }}">Logout</a>
  </body>
</html>
'''

@app.route('/')
def login():
    return render_template_string(login_page, error=None)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == correct_username and password == correct_password:
        return redirect(url_for('session'))
    else:
        return render_template_string(login_page, error="Incorrect username or password")

@app.route('/session')
def session():
    return render_template_string(session_page)

if __name__ == '__main__':
    app.run(debug=True)