from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'password123'}
}

login_page = '''
<form action="/login" method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
<form action="/change_email" method="post">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
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
    user = users_db.get(username)
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    return 'Login Failed. Try again.'

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('index'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        username = session['username']
        user = users_db[username]

        if user['email'] != old_email:
            return 'Old email does not match.'
        if user['password'] != confirm_password:
            return 'Incorrect password.'

        user['email'] = new_email
        return f'Email changed to {new_email} successfully.'

    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)