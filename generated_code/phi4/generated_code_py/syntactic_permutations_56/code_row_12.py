from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users = {
    "user1": {"password": "password123", "email": "user1@example.com"}
}

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method=post action="/login">
  <label>Username: <input type=text name=username></label><br>
  <label>Password: <input type=password name=password></label><br>
  <input type=submit value=Login>
</form>
'''

change_email_page = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method=post action="/change-email">
  <label>Old Password: <input type=password name=old_password></label><br>
  <label>New Email: <input type=text name=new_email></label><br>
  <label>Confirm New Password: <input type=password name=confirm_new_password></label><br>
  <input type=submit value=Change Email>
</form>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users.get(username)
        if user and user['password'] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_password = request.form['old_password']
        new_email = request.form['new_email']
        confirm_new_password = request.form['confirm_new_password']
        
        username = session['username']
        user = users.get(username)
        
        if user and user['password'] == old_password:
            if new_email != user['email']:
                if confirm_new_password == old_password:  # Assuming password confirmation logic
                    users[username]['email'] = new_email
                    return "<h2>Email changed successfully!</h2>"
                else:
                    return "<h2>Confirm password does not match the current password.</h2>"
            else:
                return "<h2>New email must be different from the old one.</h2>"
        else:
            return "<h2>Invalid credentials.</h2>"
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)


