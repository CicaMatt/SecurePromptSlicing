from flask import Flask, request, render_template_string
import hashlib

app = Flask(__name__)

registration_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Register</title>
  </head>
  <body>
    <h1>Register</h1>
    <form method="post" action="/register">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username" required><br><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password" required><br><br>
      <button type="submit">Register</button>
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(registration_page)

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    # Here you would insert the username and hashed_password into a database
    print(f"Username: {username}, Hashed Password: {hashed_password}")
    
    return f"User {username} registered successfully!"

if __name__ == '__main__':
    app.run(debug=True)