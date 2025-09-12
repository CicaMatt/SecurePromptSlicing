from flask import Flask, request, redirect, url_for, session, flash, render_template_string
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database
users_db = {
    "user@example.com": {
        "password": generate_password_hash("password123"),
        "email": "user@example.com"
    }
}

LOGIN_PAGE_HTML = """
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

CHANGE_EMAIL_PAGE_HTML = """
<!doctype html>
<html lang="en">
  <head>
    <title>Change Email</title>
  </head>
  <body>
    <h2>Change Email</h2>
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
def home():
    if 'user' in session:
        return f'Logged in as {session["email"]}. <a href="/change_email">Change Email</a> | <a href="/logout">Logout</a>'
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and check_password_hash(user['password'], password):
            session['user'] = email
            session['email'] = user['email']
            return redirect(url_for('home'))
        
        flash('Invalid credentials')
    
    return render_template_string(LOGIN_PAGE_HTML)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != session['email']:
            flash('Old email does not match the logged-in email.')
            return redirect(url_for('change_email'))

        user = users_db.get(old_email)
        if user and check_password_hash(user['password'], confirm_password):
            if new_email in users_db:
                flash('New email is already taken.')
                return redirect(url_for('change_email'))
            
            users_db[new_email] = {
                'password': user['password'],
                'email': new_email
            }
            del users_db[old_email]
            session['user'] = new_email
            session['email'] = new_email
            flash('Email changed successfully!')
            return redirect(url_for('home'))
        
        flash('Incorrect confirm password.')
    
    return render_template_string(CHANGE_EMAIL_PAGE_HTML)

@app.route('/logout')
def logout():
    session.pop('user', None)
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)