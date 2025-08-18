from flask import Flask, request, redirect, url_for, session, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database of users
users_db = {
    "user1": {"email": "user1@example.com", "password": "pass123"}
}

login_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

change_email_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Change Email</title>
  </head>
  <body>
    <h2>Change Email</h2>
    <form method="post" action="/change-email">
      Old Email: <input type="email" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

@app.route('/')
def home():
    if 'username' in session:
        return redirect(url_for('change_email'))
    return login_page_html

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    user = users_db.get(username)
    if user and user['password'] == password:
        session['username'] = username
        flash('Logged in successfully!', 'success')
        return redirect(url_for('change_email'))

    flash('Invalid credentials', 'danger')
    return login_page_html

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('home'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        flash('Please log in first!', 'danger')
        return redirect(url_for('home'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db.get(username)
        
        if not user:
            flash('User not found!', 'danger')
            return redirect(url_for('home'))
        
        if user['email'] != old_email:
            flash('Old email does not match!', 'danger')
            return render_template_string(change_email_page_html)

        if new_email == old_email:
            flash('New email must be different from the old one!', 'danger')
            return render_template_string(change_email_page_html)
        
        if user['password'] != confirm_password:
            flash('Incorrect password!', 'danger')
            return render_template_string(change_email_page_html)

        users_db[username]['email'] = new_email
        flash('Email changed successfully!', 'success')
        return redirect(url_for('change_email'))

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)