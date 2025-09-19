from flask import Flask, request, redirect, url_for, render_template_string
from werkzeug.security import check_password_hash

app = Flask(__name__)

# Dummy data for demonstration purposes
users = {
    'user1@example.com': {'password_hash': 'pbkdf2:sha256:260000$C9Xf8yGzV0aB5uUw$3d6b7c4e4d85a2e4fbaab4cdef12345678901234567890abcdef1234567890'}
}

logged_in_user = None

@app.route('/login', methods=['GET', 'POST'])
def login():
    global logged_in_user
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users.get(email)
        if user and check_password_hash(user['password_hash'], password):
            logged_in_user = email
            return redirect(url_for('change_email'))
        else:
            return render_template_string('<h1>Login Failed</h1><p>Invalid credentials.</p>')
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Email: <input type="email" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not logged_in_user:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != logged_in_user or not check_password_hash(users[logged_in_user]['password_hash'], confirm_password):
            return render_template_string('<h1>Email Change Failed</h1><p>Invalid old email or password.</p>')

        users[new_email] = users.pop(old_email)
        logged_in_user = new_email
        return render_template_string('<h1>Email Changed Successfully</h1><p>Your email has been updated to: %s</p>' % new_email)

    return render_template_string('''
        <h1>Change Email</h1>
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)