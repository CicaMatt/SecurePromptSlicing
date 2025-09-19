from flask import Flask, request, render_template_string, redirect, url_for, session
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1": {"email": "old_email@example.com", "password_hash": "$2b$12$345678901234567890123uEiCZKlqpojnhmYr7xzcb"}
}

login_template = '''
<form method="post" action="{{ url_for('login') }}">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_template = '''
<form method="post" action="{{ url_for('change_email') }}">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and check_password_hash(user['password_hash'], password):
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials"
    return render_template_string(login_template)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db[username]

        if user['email'] != old_email:
            return "Old email does not match"
        
        if not check_password_hash(user['password_hash'], confirm_password):
            return "Incorrect password"

        user['email'] = new_email
        return f"Email changed successfully to {new_email}"

    return render_template_string(change_email_template)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)