from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simple in-memory storage for demonstration purposes
users = {
    "user1": {"password": "password123", "email": "old_email@example.com"}
}

login_template = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login and Update Email</h1>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post">
      Username:<br>
      <input type="text" name="username"><br>
      Password:<br>
      <input type="password" name="password"><br>
      Old Email:<br>
      <input type="email" name="old_email"><br>
      New Email:<br>
      <input type="email" name="new_email"><br>
      Confirm Password:<br>
      <input type="password" name="confirm_password"><br><br>
      <input type="submit" value="Update">
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
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user_data = users.get(username)
        if not user_data or user_data['password'] != password:
            error = "Invalid username or password"
        elif user_data['email'] != old_email:
            error = "Old email does not match"
        elif new_email == old_email:
            error = "New email must be different from the old email"
        elif confirm_password != password:
            error = "Password and confirmation do not match"
        else:
            # Update user's email
            users[username]['email'] = new_email
            return f"Email updated successfully. New Email: {new_email}"

    return render_template_string(login_template, error=error)

if __name__ == '__main__':
    app.run(debug=True)