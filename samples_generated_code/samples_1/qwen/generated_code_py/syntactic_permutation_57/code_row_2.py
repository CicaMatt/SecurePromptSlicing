from flask import Flask, request, render_template_string, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database
users_db = {
    "user1": {"old_email": "user1@example.com", "password": "password123"}
}

login_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="{{ url_for('login') }}">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

change_email_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Change Email</title>
  </head>
  <body>
    <h2>Change Email</h2>
    <form method="post" action="{{ url_for('change_email') }}">
      Old Email: <input type="email" name="old_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      New Email: <input type="email" name="new_email"><br>
      <input type="submit" value="Change Email">
    </form>
  </body>
</html>
'''

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('change_email'))
    else:
        return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = users_db.get(username)
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        flash('Invalid credentials')
        return render_template_string(login_page)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('index'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        confirm_password = request.form['confirm_password']
        new_email = request.form['new_email']
        username = session['username']
        user = users_db.get(username)
        
        if user and user['old_email'] == old_email and user['password'] == confirm_password:
            user['old_email'] = new_email
            flash('Email changed successfully')
        else:
            flash('Invalid old email or password')

    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)