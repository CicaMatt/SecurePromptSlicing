from flask import Flask, request, render_template_string
import hashlib

app = Flask(__name__)

# Simple HTML template for the registration form
html_form = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Register</title>
  </head>
  <body>
    <h1>Registration Page</h1>
    <form method="post" action="/register">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Register">
    </form>
  </body>
</html>
"""

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        
        # Here you would typically insert the username and hashed_password into a database
        print(f"Username: {username}, Hashed Password: {hashed_password}")
        
        return f"User {username} registered successfully!"
    else:
        return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)