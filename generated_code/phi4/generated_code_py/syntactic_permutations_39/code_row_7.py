from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple data storage for demonstration purposes
USERS = {
    'user1': 'password123',
    'admin': 'adminpass'
}

LOGIN_PAGE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

SESSION_PAGE = '''
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
def home():
    return render_template_string(LOGIN_PAGE)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if USERS.get(username) == password:
        return redirect(url_for('session'))
    else:
        return "<h2>Incorrect username or password</h2><a href='/'>Try again</a>"

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE)

@app.route('/logout')
def logout():
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)