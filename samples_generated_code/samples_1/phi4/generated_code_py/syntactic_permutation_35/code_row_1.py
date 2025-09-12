from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a simple "database" of users
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

login_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Form</h2>
    <form method="POST" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

home_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home Page</title>
  </head>
  <body>
    <h1>Welcome to the Home Page!</h1>
    <p><a href="/login">Logout and go back to Login</a></p>
  </body>
</html>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    if users_db.get(username) == password:
        return redirect('/home')
    else:
        return redirect('/login')

@app.route('/home')
def home():
    return render_template_string(home_page_html)

if __name__ == '__main__':
    app.run(debug=True)