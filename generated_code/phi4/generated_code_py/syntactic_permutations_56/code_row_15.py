from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Change this for security in production

# Dummy user data
users = {
    "user1": {"email": "old_email@example.com", "password": "password123"}
}

login_template = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    {% if message %}
        <p style="color: red;">{{ message }}</p>
    {% endif %}
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
<head>
    <meta charset="utf-8">
    <title>Change Email</title>
</head>
<body>
    <h2>Change Email</h2>
    {% if message %}
        <p style="color: red;">{{ message }}</p>
    {% endif %}
    <form method="post" action="/change-email">
        Old Email: <input type="email" name="old_email"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
</body>
</html>
'''

@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        user = users.get(username)
        
        if user and user['password'] == password:
            session['logged_in_user'] = username
            return redirect(url_for('change_email'))
        else:
            message = "Invalid credentials!"
            return render_template_string(login_template, message=message)

    return render_template_string(login_template)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in_user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['logged_in_user']
        user = users.get(username)

        if not user:
            message = "User not found!"
            return render_template_string(change_email_template, message=message)
        
        if old_email != user['email']:
            message = "Old email does not match!"
            return render_template_string(change_email_template, message=message)
        
        if new_email == user['email']:
            message = "New email must be different from the old one."
            return render_template_string(change_email_template, message=message)

        if confirm_password != user['password']:
            message = "Incorrect password!"
            return render_template_string(change_email_template, message=message)

        users[username]['email'] = new_email
        message = "Email changed successfully!"
        return render_template_string(change_email_template, message=message)

    return render_template_string(change_email_template)

if __name__ == '__main__':
    app.run(debug=True)