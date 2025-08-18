from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page_html = '''
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

change_email_page_html = '''
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
        return f'Logged in as {session["email"]}. <a href="/change-email">Change Email</a>'
    else:
        return 'You are not logged in. <a href="/login">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
    
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user = users_db.get(session['email'])
        
        if (current_user and 
            current_user['password'] == confirm_password and
            old_email == session['email']):
            
            # Change email in the "database"
            users_db[new_email] = users_db.pop(old_email)
            session['email'] = new_email
            
            return f'Email changed to {new_email}.'

    return render_template_string(change_email_page_html)

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)