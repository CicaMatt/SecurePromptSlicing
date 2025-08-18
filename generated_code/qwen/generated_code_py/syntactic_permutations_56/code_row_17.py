from flask import Flask, request, render_template_string, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy user data for demonstration purposes
users = {
    "user1": {"email": "user1@example.com", "password_hash": "pbkdf2:sha256:150000$abc123$def456"}  # Password is 'securepassword'
}

login_template = '''
<!doctype html>
<html lang="en">
<head><title>Login</title></head>
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

change_email_template = '''
<!doctype html>
<html lang="en">
<head><title>Change Email</title></head>
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

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        if user and check_password_hash(user['password_hash'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template_string(login_template)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))

    user = users[session['username']]
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != user['email']:
            flash('Old email does not match.')
        elif old_email == new_email:
            flash('New email must be different from the old email.')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password.')
        else:
            user['email'] = new_email
            flash('Email updated successfully!')
            return redirect(url_for('change_email'))

    return render_template_string(change_email_template)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)