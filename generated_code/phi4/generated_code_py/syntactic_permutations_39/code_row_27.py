from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple user database for demonstration purposes.
USER_DB = {
    'user1': 'password123',
    'admin': 'securepass'
}

LOGIN_PAGE_TEMPLATE = """
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
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

SESSION_PAGE_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h2>Welcome to the Session Page!</h2>
    <p>You are logged in successfully.</p>
    <a href="/logout">Logout</a>
  </body>
</html>
"""

@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if USER_DB.get(username) == password:
            return render_template_string(SESSION_PAGE_TEMPLATE)
        else:
            return "Invalid username or password."
    
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/logout')
def logout():
    # In a real application, handle session cleanup here.
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)