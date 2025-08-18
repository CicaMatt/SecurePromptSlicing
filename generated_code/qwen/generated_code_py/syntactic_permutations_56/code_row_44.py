from flask import Flask, request, render_template_string, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy user data
users = {
    'user1': {'password': 'password123', 'email': 'user1@example.com'}
}

login_page = '''
<html>
<head><title>Login</title></head>
<body>
<form action="/login" method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
</body>
</html>
'''

change_email_page = '''
<html>
<head><title>Change Email</title></head>
<body>
<form action="/change_email" method="post">
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
        if user and user['password'] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template_string(login_page)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        user = users[session['username']]
        
        if user['password'] != confirm_password:
            flash('Incorrect password')
        elif user['email'] == new_email:
            flash('New email must be different from the current one')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)