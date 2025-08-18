from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple in-memory data storage for demonstration purposes
users_db = {
    'user@example.com': {'password': 'password123', 'email': 'user@example.com'}
}

LOGIN_PAGE_TEMPLATE = '''
<!doctype html>
<html>
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

CHANGE_EMAIL_PAGE_TEMPLATE = '''
<!doctype html>
<html>
  <body>
    <h2>Change Email</h2>
    <form method="post" action="/change_email">
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
        return f'<h1>Welcome {session["email"]}</h1><a href="/change_email">Change Email</a>'
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        user = users_db.get(email)
        
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
        else:
            return 'Login failed', 401

    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db.get(old_email)
        
        if user and session['email'] == old_email and user['password'] == confirm_password:
            if new_email in users_db:
                return 'New email already exists', 400
            else:
                del users_db[old_email]
                users_db[new_email] = {'password': user['password'], 'email': new_email}
                session['email'] = new_email
                return redirect(url_for('home'))
        else:
            return 'Invalid credentials or email', 401

    return render_template_string(CHANGE_EMAIL_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)