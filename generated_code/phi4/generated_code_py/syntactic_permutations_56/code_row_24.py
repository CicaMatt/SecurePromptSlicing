from flask import Flask, request, session, redirect, url_for, render_template_string, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulating a database with an in-memory dictionary
users_db = {
    "user1": {"password": "pass123", "email": "user1@example.com"}
}

login_page_html = '''
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
{% if not logged_in %}
    <p>You must be logged in to change your email.</p>
    <a href="{{ url_for('login') }}">Go to login page</a>
{% else %}
<form method="post">
  New Email: <input type="email" name="new_email"><br>
  Confirm Password: <input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
{% endif %}
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        
        if user and user['password'] == password:
            session['username'] = username
            flash('Logged in successfully.', 'success')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials.', 'danger')

    return render_template_string(login_page_html)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))

    logged_in = True
    username = session['username']
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(username)
        
        if not user or user['password'] != confirm_password:
            flash('Invalid password.', 'danger')
        elif new_email == user['email']:
            flash('New email must be different from the old one.', 'danger')
        else:
            user['email'] = new_email
            flash('Email changed successfully!', 'success')

    return render_template_string(change_email_page_html, logged_in=logged_in)

if __name__ == '__main__':
    app.run(debug=True)