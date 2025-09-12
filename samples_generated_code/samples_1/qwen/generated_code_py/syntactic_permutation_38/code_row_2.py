from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "admin": "password123"
}

login_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    {% if error %}
      <p style="color: red;">Invalid username or password</p>
    {% endif %}
    <form method="post" action="/login">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect('/dashboard')
        else:
            return render_template_string(login_page, error=True)
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)