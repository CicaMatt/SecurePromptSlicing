from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user credentials database
USER_CREDENTIALS = {
    "username": "user1",
    "password": "password123"
}

login_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
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

session_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h2>Welcome to the Session Page!</h2>
    <p>You have successfully logged in.</p>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

@app.route('/')
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    if username == USER_CREDENTIALS["username"] and password == USER_CREDENTIALS["password"]:
        return redirect(url_for('session'))
    else:
        error_message = "Invalid username or password."
        return render_template_string(login_page_html, error=error_message)

@app.route('/session')
def session():
    return render_template_string(session_page_html)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)