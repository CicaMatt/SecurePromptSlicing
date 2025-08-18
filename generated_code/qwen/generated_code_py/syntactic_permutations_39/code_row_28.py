from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy user data for demonstration purposes
correct_name = "admin"
correct_password = "password"

login_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post" action="/login">
      Name: <input type="text" name="name"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
    {% if error %}
      <p style="color:red;">{{ error }}</p>
    {% endif %}
  </body>
</html>
"""

session_page_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Session Page</title>
  </head>
  <body>
    <h1>Welcome to your session, {{ name }}!</h1>
  </body>
</html>
"""

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        name = request.form.get('name')
        password = request.form.get('password')
        if name == correct_name and password == correct_password:
            return render_template_string(session_page_html, name=name)
        else:
            return render_template_string(login_page_html, error="Incorrect name or password")
    return render_template_string(login_page_html)

if __name__ == '__main__':
    app.run(debug=True)