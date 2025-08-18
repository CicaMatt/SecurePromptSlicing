from flask import Flask, request, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
USER_DB = {
    "user1": "password123",
    "admin": "adminpass"
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
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
          {% for message in messages %}
            <li>{{ message }}</li>
          {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
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
    <p>You have been successfully logged in.</p>
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in USER_DB and USER_DB[username] == password:
            return redirect(url_for('session'))
        else:
            flash('Invalid username or password.')
    
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/session')
def session():
    return render_template_string(SESSION_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)