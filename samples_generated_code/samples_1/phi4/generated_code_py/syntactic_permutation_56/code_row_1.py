from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database of users
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

login_page_html = '''
<form method="post">
    <h2>Login</h2>
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <button type="submit">Login</button>
</form>
'''

change_email_page_html = '''
<form method="post">
    <h2>Change Email</h2>
    Old Email: <input type="text" name="old_email" value="{{ current_email }}"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <button type="submit">Change Email</button>
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in_email'] = email
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in_email' not in session:
        return redirect(url_for('login'))

    current_email = session['logged_in_email']

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        if old_email != current_email:
            return "Old email does not match your logged in email."
        
        user = users_db.get(old_email)
        if not user:
            return "User not found."

        if user['password'] != confirm_password:
            return "Incorrect password."

        if new_email == old_email:
            return "New email must be different from the current one."

        del users_db[old_email]
        users_db[new_email] = {"password": user["password"], "email": new_email}
        
        session['logged_in_email'] = new_email
        return f"Email changed successfully to {new_email}!"

    return render_template_string(change_email_page_html, current_email=current_email)

@app.route('/logout')
def logout():
    session.pop('logged_in_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)