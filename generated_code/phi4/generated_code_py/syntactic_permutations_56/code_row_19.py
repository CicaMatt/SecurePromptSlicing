from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database for demonstration purposes
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page_html = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Email: <input type="text" name="email"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

change_email_page_html = """
<!doctype html>
<title>Change Email</title>
<h2>Change Email Page</h2>
<form method="post">
  Old Email: <input type="text" name="old_email"><br>
  New Email: <input type="text" name="new_email"><br>
  Confirm Password: <input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        user = users_db.get(email)

        if user and user['password'] == password:
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            return "Login Failed. Please try again."
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user_email = session.get('user_email')
        user = users_db.get(user_email)

        if not user or user['email'] != old_email or user['password'] != confirm_password:
            return "Invalid old email or password."

        if new_email == old_email:
            return "New email must be different from the old one."
        
        # Update email in the database
        users_db[user_email]['email'] = new_email

        session.pop('user_email', None)  # Logout after changing email
        return redirect(url_for('login'))

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)