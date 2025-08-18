from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    "user@example.com": {"password": "password123"}
}

login_page = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Email: <input type="email" name="email"><br>
      Password: <input type="password" name="password"><br>
      <button type="submit">Login</button>
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
      Old Email: <input type="email" name="old_email"><br>
      New Email: <input type="email" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <button type="submit">Change Email</button>
    </form>
  </body>
</html>
'''

@app.route('/')
def home():
    if 'user' in session:
        return f"<h1>Welcome, {session['user']}! <a href='/change-email'>Change Email</a></h1>"
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['user'] = email
            return redirect(url_for('home'))
    
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        current_user = users_db.get(session['user'])

        if (current_user and
            current_user['password'] == confirm_password and
            old_email == session['user'] and
            old_email != new_email):
            
            users_db.pop(old_email)
            users_db[new_email] = {'password': current_user['password']}
            session['user'] = new_email
            return f"<h1>Email changed to {new_email}</h1>"
        
        return "<h1>Invalid credentials or emails. Try again.</h1>"

    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)