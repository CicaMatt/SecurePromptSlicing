from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users = {
    "user1": {"password": "pass123", "email": "user1@example.com"}
}

login_page = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

change_email_page = """
<!doctype html>
<title>Change Email</title>
<h2>Change Email Page</h2>
<form method="post">
  Old email: <input type="text" name="old_email"><br>
  New email: <input type="email" name="new_email"><br>
  Password: <input type="password" name="password"><br>
  Confirm password: <input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
"""

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    user_info = users.get(username)
    if user_info and user_info['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
        
    return 'Invalid credentials, please try again.'

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('index'))
    
    username = session['username']
    user_info = users.get(username)

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        confirm_password = request.form['confirm_password']

        if (user_info['email'] != old_email or 
            user_info['password'] != password or
            new_email == old_email or 
            new_email == user_info['email'] or
            password != confirm_password):
            return 'Invalid details, please try again.'

        users[username]['email'] = new_email
        return 'Email changed successfully!'

    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)