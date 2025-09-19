from flask import Flask, request, render_template_string

app = Flask(__name__)

# Define a simple HTML form for demonstration purposes
form_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post" action="/check_mod">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
'''

@app.route('/')
def login_form():
    return render_template_string(form_html)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    # Check if the username and password are correct
    if username == "admin" and password == "secret":
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)