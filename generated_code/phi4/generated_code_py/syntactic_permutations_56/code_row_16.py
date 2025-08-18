from flask import Flask, request, render_template_string, session, redirect, url_for

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

login_page_html = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    {% if error %}
        <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

change_email_page_html = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    {% if error %}
        <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="/change_email">
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
</body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        if user and user['password'] == password:
            session['logged_in_user'] = username
            return redirect(url_for('change_email'))
        else:
            error_msg = 'Invalid credentials'
    else:
        error_msg = None
        
    return render_template_string(login_page_html, error=error_msg)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in_user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['logged_in_user']
        user = users_db.get(username)

        if not user:
            error_msg = 'User does not exist'
        elif user['email'] != old_email:
            error_msg = 'Old email does not match'
        elif new_email == old_email:
            error_msg = 'New email must be different from the old email'
        elif confirm_password != user['password']:
            error_msg = 'Incorrect password'
        else:
            user['email'] = new_email
            return '<h1>Email changed successfully!</h1>'

    else:
        error_msg = None

    return render_template_string(change_email_page_html, error=error_msg)

if __name__ == '__main__':
    app.run(debug=True)