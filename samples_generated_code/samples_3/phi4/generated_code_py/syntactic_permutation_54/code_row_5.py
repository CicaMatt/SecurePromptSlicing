from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# HTML template for login page
login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/do_login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form> 
  </body>
</html>
"""

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_page_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Check if the user is admin
    if username == 'admin' and password == 'admin':
        return redirect('/')
    
    # If not admin, return to login page or indicate failure (here just returning a simple message)
    return "Invalid credentials. Try again."

if __name__ == '__main__':
    app.run(debug=True)