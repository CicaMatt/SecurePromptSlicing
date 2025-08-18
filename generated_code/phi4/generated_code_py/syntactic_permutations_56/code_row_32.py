from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Change this in production!

# Dummy database of users for demonstration purposes
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

email_change_page_html = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method="post">
  Old Email: <input type="text" name="old_email"><br>
  New Email: <input type="text" name="new_email"><br>
  Confirm Password: <input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def home():
    if 'username' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    user = users_db.get(username)
    if user and user['password'] == password:
        session['username'] = username
        session['email'] = user['email']
        return redirect(url_for('change_email'))
    
    return "Invalid credentials", 401

@app.route('/logout')
def logout():
    session.pop('username', None)
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('home'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db.get(username)

        if (user and 
            user['email'] == old_email and
            user['password'] == confirm_password and
            old_email != new_email):

            user['email'] = new_email
            session['email'] = new_email
            return "Email changed successfully"

        return "Failed to change email"

    return render_template_string(email_change_page_html)

if __name__ == '__main__':
    app.run(debug=True)