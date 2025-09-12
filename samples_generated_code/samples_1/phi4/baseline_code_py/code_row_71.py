from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy data for demonstration purposes
users = {
    "user1": {"password": "pass123", "email": "old@example.com"}
}

login_page = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
{% if not session.get('logged_in') %}
    <p>You must be logged in to change your email.</p>
{% else %}
    <form method="post">
        Old Email: <input type="email" name="old_email"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
{% endif %}
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users.get(username)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = user['email']
            return redirect(url_for('change_email'))
        else:
            return "Invalid username or password"
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    old_email = session['user_email']
    
    if request.method == 'POST':
        old_email_input = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != old_email_input:
            return "Old email does not match"
        
        username = [user for user, details in users.items() if details["email"] == old_email][0]
        password = users[username]['password']
        
        if password != confirm_password:
            return "Incorrect password"

        if new_email == old_email:
            return "New email must be different from old email"

        users[username]['email'] = new_email
        session['user_email'] = new_email
        return f"Email changed successfully to {new_email}"

    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)