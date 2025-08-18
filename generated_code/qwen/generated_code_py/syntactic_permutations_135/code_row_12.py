from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_FORM = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <form method="post" action="/">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        return str(check_credentials(username, password)).lower()
    return render_template_string(HTML_FORM)

def check_credentials(username, password):
    correct_username = "admin"
    correct_password = "secret"
    return username == correct_username and password == correct_password

if __name__ == '__main__':
    app.run(debug=True)