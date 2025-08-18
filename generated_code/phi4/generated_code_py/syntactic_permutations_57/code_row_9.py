from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy in-memory database for demonstration purposes
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

login_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

change_email_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Change Email</title>
  </head>
  <body>
    <h2>Change Email</h2>
    <form method="post" action="/change_email">
      Old email: <input type="text" name="old_email"><br>
      New email: <input type="text" name="new_email"><br>
      Confirm password: <input type="password" name="confirm_password"><br><br>
      <input type="submit" value="Change Email">
    </form>
  </body>
</html>
'''

@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        user = users_db.get(username)
        if user and user['password'] == password:
            response = redirect(url_for('change_email'))
            response.set_cookie('logged_in', 'true')  # Set a cookie to indicate the user is logged in
            return response
        
    return render_template_string(login_page_html)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not request.cookies.get('logged_in'):
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        for username, user in users_db.items():
            if user['email'] == old_email and user['password'] == confirm_password:
                user['email'] = new_email
                return f"Email changed successfully to {new_email}."
        
        return "Invalid credentials or email."

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)