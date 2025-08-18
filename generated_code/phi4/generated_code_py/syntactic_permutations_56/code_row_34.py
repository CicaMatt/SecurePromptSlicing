from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database for demonstration purposes
users_db = {
    "user1": {"password": "password123", "email": "old@example.com"}
}

login_page_html = '''
<form method="post">
    <h2>Login</h2>
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
<form method="post">
    <h2>Change Email</h2>
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        
        if user and user['password'] == password:
            session['user'] = username
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['user']
        user = users_db.get(username)

        if user and user['email'] == old_email and user['password'] == confirm_password:
            if old_email != new_email:
                user['email'] = new_email
                return f"Email changed to {new_email}"
            else:
                return "New email must be different from the old one."
        elif user['password'] != confirm_password:
            return "Incorrect password."

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)