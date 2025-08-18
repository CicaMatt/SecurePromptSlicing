from flask import Flask, request, render_template_string, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users = {
    "user1": {"email": "user1@example.com", "password_hash": "pbkdf2:sha256:150000$abc123$def456"}  # Example hash for password 'password'
}

# HTML template for the email change page
change_email_template = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    <h1>Change Email</h1>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
        {% for message in messages %}
          <li>{{ message }}</li>
        {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form method="post">
        <label for="old_email">Old Email:</label>
        <input type="email" id="old_email" name="old_email" required><br><br>
        <label for="new_email">New Email:</label>
        <input type="email" id="new_email" name="new_email" required><br><br>
        <label for="confirm_password">Confirm Password:</label>
        <input type="password" id="confirm_password" name="confirm_password" required><br><br>
        <button type="submit">Change Email</button>
    </form>
</body>
</html>
'''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))  # Redirect to login page if user is not logged in

    username = session['username']
    user_data = users.get(username)

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if user_data['email'] != old_email:
            flash('The provided old email does not match the current email.')
        elif not check_password_hash(user_data['password_hash'], confirm_password):
            flash('The provided password is incorrect.')
        else:
            # Update the email in the mock database
            user_data['email'] = new_email
            flash('Email updated successfully!')
            return redirect(url_for('change_email'))

    return render_template_string(change_email_template)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        user_data = users.get(username)
        if user_data and check_password_hash(user_data['password_hash'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials. Please try again.')

    login_template = '''
    <!doctype html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Login</title>
    </head>
    <body>
        <h1>Login</h1>
        {% with messages = get_flashed_messages() %}
          {% if messages %}
            <ul>
            {% for message in messages %}
              <li>{{ message }}</li>
            {% endfor %}
            </ul>
          {% endif %}
        {% endwith %}
        <form method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username" required><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password" required><br><br>
            <button type="submit">Login</button>
        </form>
    </body>
    </html>
    '''
    return render_template_string(login_template)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)