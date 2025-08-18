from flask import Flask, request, render_template_string, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'password123'}
}

login_form = '''
<form method="post" action="/login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_form = '''
<form method="post" action="/change_email">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def index():
    if 'username' in session:
        return f'Logged in as {session["username"]}<br><a href="/change_email">Change Email</a><br><a href="/logout">Logout</a>'
    return login_form

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and user['password'] == password:
            session['username'] = username
            return redirect(url_for('index'))
        else:
            flash('Invalid username or password')
    return login_form

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db[session['username']]
        if user['email'] != old_email:
            flash('Old email does not match the current one.')
        elif user['password'] != confirm_password:
            flash('Incorrect password.')
        else:
            user['email'] = new_email
            flash('Email updated successfully!')
            return redirect(url_for('index'))

    return change_email_form

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)