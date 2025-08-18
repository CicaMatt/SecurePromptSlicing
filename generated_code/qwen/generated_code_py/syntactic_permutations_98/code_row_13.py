from flask import Flask, request, render_template_string

app = Flask(__name__)

registration_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Registration Page</title>
  </head>
  <body>
    <h1>Register</h1>
    <form method="post">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Register">
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # Here you would typically add code to save the username and password securely
        return f"Registered with username: {username} and password: {password}"
    return render_template_string(registration_form)

if __name__ == '__main__':
    app.run(debug=True)