from flask import Flask, request, render_template_string, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database simulation
users_db = {
    'user1': {'password': 'password123', 'email': 'old_email@example.com'}
}

login_page = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h1>Login</h1>
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

change_email_page = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    <h1>Change Email</h1>
    <form method="post" action="/change_email">
        Old Email: <input type="email" name="old_email"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    <a href="/logout">Logout</a>
</body>
</html>
'''

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user_info = users_db.get(username)
    if user_info and user_info['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        flash('Invalid credentials')
        return render_template_string(login_page)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user_info = users_db[username]
        
        if user_info['email'] != old_email:
            flash('Old email does not match.')
        elif user_info['password'] != confirm_password:
            flash('Incorrect password.')
        else:
            user_info['email'] = new_email
            flash('Email changed successfully.')
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)