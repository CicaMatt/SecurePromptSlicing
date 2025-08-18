from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

login_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

home_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home Page</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
  </body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        # Check if user exists in the database
        if username in users_db and users_db[username] == password:
            return redirect('/home')
        else:
            return redirect('/login')
    return render_template_string(login_html)

@app.route('/')
def index():
    return redirect('/login')

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    app.run(debug=True)