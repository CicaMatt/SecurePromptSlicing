from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1@example.com": {"password": "securepassword", "email": "user1@example.com"}
}

# Login status tracker
logged_in_user = None

@app.route('/login', methods=['GET', 'POST'])
def login():
    global logged_in_user
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if email in users_db and users_db[email]['password'] == password:
            logged_in_user = email
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if logged_in_user is None:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != logged_in_user or users_db[logged_in_user]['password'] != confirm_password:
            return "Invalid old email or password"

        users_db[new_email] = users_db.pop(old_email)
        users_db[new_email]['email'] = new_email
        logged_in_user = new_email

        return f"Email changed successfully to {new_email}"
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)