from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database of users
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Email: <input type="text" name="email"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

change_email_page = '''
<!doctype html>
<html lang="en">
  <head><title>Change Email</title></head>
  <body>
    <h2>Change Email</h2>
    <form method="post" action="/change-email">
      Old Email: <input type="text" name="old_email"><br>
      New Email: <input type="text" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
  </body>
</html>
'''

@app.route('/')
def home():
    if 'email' in session:
        return f'<h1>Welcome, {session["email"]}</h1><a href="/change-email">Change Email</a> <br> <a href="/logout">Logout</a>'
    else:
        return '<h1>Please login first</h1>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
        
        return '<h1>Invalid credentials</h1>'
    
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user_email = session['email']
        
        if old_email != current_user_email:
            return '<h1>Old email does not match your logged-in email</h1>'
        
        if old_email == new_email:
            return '<h1>New email must be different from the old one</h1>'
        
        user = users_db.get(current_user_email)
        if user and user['password'] == confirm_password:
            # Update user data
            del users_db[current_user_email]
            users_db[new_email] = {"password": user['password'], "email": new_email}
            session['email'] = new_email
            return redirect(url_for('home'))

        return '<h1>Incorrect password</h1>'
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)