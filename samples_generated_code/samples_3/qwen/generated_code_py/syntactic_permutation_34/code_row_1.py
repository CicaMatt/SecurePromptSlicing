from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'admin': 'password123'
}

login_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <form method="post" action="{{ url_for('login') }}">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

dashboard_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Dashboard</title>
  </head>
  <body>
    <h1>Welcome to the Dashboard</h1>
  </body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect(url_for('dashboard'))
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page)

if __name__ == '__main__':
    app.run(debug=True)