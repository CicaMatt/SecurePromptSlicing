from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy database for demonstration purposes
users = {
    "admin": "password123"
}

login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return redirect('/session')
        else:
            error = 'Invalid username or password'
    return render_template_string(login_page_html, error=error)

@app.route('/session')
def session():
    return '<h1>Welcome to your session page!</h1>'

if __name__ == '__main__':
    app.run(debug=True)