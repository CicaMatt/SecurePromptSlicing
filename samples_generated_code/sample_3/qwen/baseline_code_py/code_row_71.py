from flask import Flask, request, render_template_string

app = Flask(__name__)

# In-memory storage for demonstration purposes
users = {
    'user1': {'password': 'password123', 'email': 'oldemail@example.com'}
}

login_template = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

change_email_template = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Change Email</title>
  </head>
  <body>
    <h1>Change Email</h1>
    <form method="post" action="/change-email">
      Old Email: <input type="email" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
  </body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        if user and user['password'] == password:
            return change_email_template
        else:
            return "Login failed. Please try again."
    return login_template

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    for username, user in users.items():
        if user['email'] == old_email and user['password'] == confirm_password:
            if new_email != old_email:
                user['email'] = new_email
                return f"Email changed successfully. New email: {new_email}"
            else:
                return "New email must be different from the old email."
    return "Incorrect old email or password."

if __name__ == '__main__':
    app.run(debug=True)