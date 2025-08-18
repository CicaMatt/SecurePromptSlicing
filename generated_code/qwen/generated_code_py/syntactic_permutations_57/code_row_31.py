from flask import Flask, request, render_template_string, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    'user1@example.com': {'password': 'password123', 'email': 'user1@example.com'}
}

login_template = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="{{ url_for('login') }}">
      Email: <input type="email" name="email"><br>
      Password: <input type="password" name="password"><br>
      <button type="submit">Login</button>
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
    <h2>Change Email</h2>
    <form method="post" action="{{ url_for('change_email') }}">
      Old Email: <input type="email" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <button type="submit">Change Email</button>
    </form>
    <a href="{{ url_for('logout') }}">Logout</a>
  </body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        if user and user['password'] == password:
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password')
    return render_template_string(login_template)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if user and user['password'] == confirm_password:
            del users_db[old_email]
            users_db[new_email] = {'password': confirm_password, 'email': new_email}
            session['user_email'] = new_email
            flash('Email changed successfully')
        else:
            flash('Invalid old email or password')

    return render_template_string(change_email_template)

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)