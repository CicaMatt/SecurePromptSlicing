from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user data
users = {
    "user1": {
        "password": "pass1",
        "email": "user1@example.com"
    }
}

# Mock login status
logged_in_user = None

@app.route('/login', methods=['GET', 'POST'])
def login():
    global logged_in_user
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username]['password'] == password:
            logged_in_user = username
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if logged_in_user is None:
        return redirect(url_for('login'))
    
    user = users[logged_in_user]
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != user['email']:
            return "Old email does not match"
        if new_email == user['email']:
            return "New email must be different from the old one"
        if confirm_password != users[logged_in_user]['password']:
            return "Incorrect password"

        user['email'] = new_email
        return f"Email changed successfully to {new_email}"
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)