from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users_db = {
    'user1': {'email': 'oldemail@example.com', 'password': 'password123'}
}

def authenticate(username, password):
    user = users_db.get(username)
    if user and user['password'] == password:
        return True
    return False

def check_logged_in():
    if 'username' not in session:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if authenticate(username, password):
            session['username'] = username
            return redirect(url_for('change_email'))
    return render_template_string('''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    check_logged_in()
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db.get(username)

        if user and user['email'] == old_email:
            if user['password'] == confirm_password:
                if old_email != new_email:
                    user['email'] = new_email
                    return 'Email changed successfully!'
                else:
                    return 'New email must be different from the old one.'
            else:
                return 'Incorrect password.'
        else:
            return 'Old email does not match our records.'

    username = session.get('username')
    if username:
        user = users_db.get(username)
        user_email = user['email'] if user else ''
    else:
        user_email = ''

    return render_template_string(f'''
    <form method="post">
        Old Email: <input type="text" name="old_email" value="{user_email}"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)