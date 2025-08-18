from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users_db = {
    "user@example.com": {
        "password": "password123"
    }
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
        return f'<h1>Welcome {session["email"]}</h1><a href="/change-email">Change email</a>'
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
        
        return '<h3>Invalid credentials</h3>' + login_page
    
    return login_page

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    current_email = session['email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != current_email or new_email == old_email:
            return '<h3>Invalid email details</h3>' + change_email_page
        
        user = users_db.get(current_email)
        if not user or user['password'] != confirm_password:
            return '<h3>Incorrect password</h3>' + change_email_page

        # Update the database
        del users_db[current_email]
        users_db[new_email] = {'password': user['password']}
        
        session['email'] = new_email
        
        return redirect(url_for('home'))
    
    return change_email_page

if __name__ == '__main__':
    app.run(debug=True)