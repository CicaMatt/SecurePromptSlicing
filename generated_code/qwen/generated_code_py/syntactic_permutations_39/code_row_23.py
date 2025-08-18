from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simple in-memory user database
users = {
    "admin": "password123"
}

login_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="/">
      Username:<br>
      <input type="text" name="username"><br>
      Password:<br>
      <input type="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form> 
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return f"Welcome {username}!"
        else:
            error = 'Invalid username or password'
    return render_template_string(login_form, error=error)

if __name__ == '__main__':
    app.run(debug=True)