from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": "password1",
    "user2": "password2"
}

login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

home_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
  </body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username in users_db and users_db[username] == password:
        return redirect('/home')
    else:
        return redirect('/')

@app.route('/home')
def home():
    return render_template_string(home_page_html)

if __name__ == '__main__':
    app.run(debug=True)