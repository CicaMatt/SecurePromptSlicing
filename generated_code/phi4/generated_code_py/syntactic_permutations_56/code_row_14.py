from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated user data store
users = {
    "user1": {"email": "user1@example.com", "password": "password123"}
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

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        user = users.get(username)
        
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user'] = username
            return redirect(url_for('change_email'))
    
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return "You must be logged in to view this page."

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['user']
        
        user = users.get(username)
        
        if user and user['email'] == old_email:
            if new_email != old_email and user['password'] == confirm_password:
                user['email'] = new_email
                return "Email changed successfully."
            else:
                return "New email must be different. Or password is incorrect."

    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)