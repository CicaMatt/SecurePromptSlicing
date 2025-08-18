from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

login_page = """
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Email: <input type="email" name="email"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

change_email_page = """
<!doctype html>
<html lang="en">
  <head>
    <title>Change Email</title>
  </head>
  <body>
    <h2>Change Email</h2>
    {% if message %}
      <p>{{ message }}</p>
    {% endif %}
    <form method="post" action="/change_email">
      Old Email: <input type="email" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
  </body>
</html>
"""

@app.route('/')
def index():
    if 'user' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']

    user = users_db.get(email)
    if user and user['password'] == password:
        session['user'] = email
        return redirect(url_for('change_email'))
    
    return render_template_string(login_page, message="Invalid credentials")

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('index'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(session['user'])
        
        if user and user['email'] == old_email and user['password'] == confirm_password:
            users_db[new_email] = {"password": user["password"], "email": new_email}
            del users_db[old_email]
            session['user'] = new_email
            return render_template_string(change_email_page, message="Email changed successfully")

        return render_template_string(change_email_page, message="Invalid old email or password")
    
    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)