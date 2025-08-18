from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory storage for demonstration purposes
USER_DATA = {
    'username': 'admin',
    'password': 'password123'
}

LOGIN_PAGE_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post" action="/login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
    {% if message %}
        <p style="color: red;">{{ message }}</p>
    {% endif %}
  </body>
</html>
'''

SESSION_PAGE_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session</title>
  </head>
  <body>
    <h1>Welcome to the Session Page!</h1>
    <p>You are logged in.</p>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    message = ''
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        if username == USER_DATA['username'] and password == USER_DATA['password']:
            return redirect(url_for('session'))
        else:
            message = 'Incorrect username or password.'
    
    return render_template_string(LOGIN_PAGE_HTML, message=message)

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE_HTML)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)