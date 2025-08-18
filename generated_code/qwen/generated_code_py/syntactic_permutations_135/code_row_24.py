from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simple HTML form for demonstration purposes
form_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post" action="/check_mod">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
'''

# Correct username and password
correct_username = "admin"
correct_password = "secret"

@app.route('/')
def index():
    return render_template_string(form_html)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == correct_username and password == correct_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)