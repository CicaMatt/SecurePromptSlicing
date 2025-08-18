from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a database with a dictionary for demonstration purposes.
database = {
    'user1': 'password123',
    'user2': 'mypassword'
}

login_html = """
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Login</title>
</head>
<body>
  <h2>Login Page</h2>
  <form method="post" action="/login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
  </form>
</body>
</html>
"""

home_html = """
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Home Page</title>
</head>
<body>
  <h2>Welcome to the Home Page!</h2>
  <a href="/login">Logout and go back to login page</a>
</body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(login_html)

@app.route('/login', methods=['POST'])
def login_action():
    username = request.form['username']
    password = request.form['password']

    if database.get(username) == password:
        return redirect('/home')
    
    # If credentials are invalid, redirect to the login page again.
    return redirect('/')

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    app.run(debug=True)